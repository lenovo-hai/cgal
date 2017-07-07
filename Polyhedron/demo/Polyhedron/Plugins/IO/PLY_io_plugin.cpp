#include "Scene_polygon_soup_item.h"
#include "Scene_surface_mesh_item.h"
#include "Scene_polyhedron_item.h"
#include "Scene_points_with_normal_item.h"

#include <CGAL/Three/Polyhedron_demo_io_plugin_interface.h>
#include <QInputDialog>
#include <fstream>

#include <CGAL/IO/PLY_reader.h>
#include <CGAL/IO/PLY_writer.h>
#include <CGAL/Polygon_mesh_processing/polygon_soup_to_polygon_mesh.h>
#include <QMessageBox>

class Polyhedron_demo_ply_plugin :
  public QObject,
  public CGAL::Three::Polyhedron_demo_io_plugin_interface
{
  Q_OBJECT
  Q_INTERFACES(CGAL::Three::Polyhedron_demo_io_plugin_interface)
  Q_PLUGIN_METADATA(IID "com.geometryfactory.PolyhedronDemo.IOPluginInterface/1.0")

public:
  QString name() const { return "ply_plugin"; }
  QString nameFilters() const { return "PLY files (*.ply)"; }
  bool canLoad() const;
  CGAL::Three::Scene_item* load(QFileInfo fileinfo);

  bool canSave(const CGAL::Three::Scene_item*);
  bool save(const CGAL::Three::Scene_item*, QFileInfo fileinfo);
};

bool Polyhedron_demo_ply_plugin::canLoad() const {
  return true;
}

CGAL::Three::Scene_item*
Polyhedron_demo_ply_plugin::load(QFileInfo fileinfo) {
  std::ifstream in(fileinfo.filePath().toUtf8(), std::ios_base::binary);

  if(!in)
    std::cerr << "Error!\n";

  // Test if input is mesh or point set
  bool input_is_mesh = false;
  std::string line;
  std::istringstream iss;
  while (getline (in,line))
  {
    iss.clear();
    iss.str (line);
    std::string keyword;
    if (iss >> keyword)
    {
      if (keyword == "element")
      {
        std::string type;
        if (iss >> type)
          if (type == "face")
          {
            input_is_mesh = true;
            break;
          }
      }
      else if (keyword == "end_header")
        break;
    }
  }

  in.seekg(0);

  if (input_is_mesh) // Open mesh or polygon soup
  {
    std::vector<Kernel::Point_3> points;
    std::vector<std::vector<std::size_t> > polygons;

    if (!(CGAL::read_PLY (in, points, polygons)))
      return NULL;

    if (CGAL::Polygon_mesh_processing::is_polygon_soup_a_polygon_mesh (polygons))
    {
      SMesh *surface_mesh = new SMesh();
      CGAL::Polygon_mesh_processing::polygon_soup_to_polygon_mesh (points, polygons,
                                                                   *surface_mesh);
      Scene_surface_mesh_item* sm_item = new Scene_surface_mesh_item(surface_mesh);
      sm_item->setName(fileinfo.completeBaseName());
      return sm_item;
    }
    else
    {
      Scene_polygon_soup_item* soup_item = new Scene_polygon_soup_item;
      soup_item->setName(fileinfo.completeBaseName());
      soup_item->load (points, polygons);
      return soup_item;
    }
  }
  else // Open point set
  {
    Scene_points_with_normal_item* item;
    item = new Scene_points_with_normal_item();
    if(!item->read_ply_point_set(in))
    {
      delete item;
      return NULL;
    }

    item->setName(fileinfo.completeBaseName());
    return item;
  }
  
  return NULL;
}

bool Polyhedron_demo_ply_plugin::canSave(const CGAL::Three::Scene_item* item)
{
  // This plugin supports point sets and any type of surface
  return (qobject_cast<const Scene_points_with_normal_item*>(item)
          || qobject_cast<const Scene_polygon_soup_item*>(item)
          || qobject_cast<const Scene_surface_mesh_item*>(item)
          || qobject_cast<const Scene_polyhedron_item*>(item));
}

bool Polyhedron_demo_ply_plugin::save(const CGAL::Three::Scene_item* item, QFileInfo fileinfo)
{
  // Check extension (quietly)
  std::string extension = fileinfo.suffix().toUtf8().data();
  if (extension != "ply" && extension != "PLY")
    return false;

  QStringList list;
  list << tr("Binary");
  list << tr("Ascii");
  bool ok = false;
  QString choice
    = QInputDialog::getItem(NULL, tr("Save PLY file"), tr("Format"), list, 0, false, &ok);

  if (!ok)
    return false;
  
  std::ofstream out(fileinfo.filePath().toUtf8().data());
  out.precision (std::numeric_limits<double>::digits10 + 2);
  
  // This plugin supports point sets
  const Scene_points_with_normal_item* point_set_item =
    qobject_cast<const Scene_points_with_normal_item*>(item);
  if (point_set_item)
    return point_set_item->write_ply_point_set(out, (choice == tr("Binary")));

  // This plugin supports polygon soups
  const Scene_polygon_soup_item* soup_item =
    qobject_cast<const Scene_polygon_soup_item*>(item);
  if (soup_item)
    return CGAL::write_PLY (out, soup_item->points(), soup_item->polygons());

  // This plugin supports surface meshes
  const Scene_surface_mesh_item* sm_item =
    qobject_cast<const Scene_surface_mesh_item*>(item);
  if (sm_item)
    return CGAL::write_PLY (out, *(sm_item->polyhedron()));

  // This plugin supports polyhedrons
  const Scene_polyhedron_item* poly_item =
    qobject_cast<const Scene_polyhedron_item*>(item);
  if (poly_item)
    return CGAL::write_PLY (out, *(poly_item->polyhedron()));

  return false;
}


#include "PLY_io_plugin.moc"
