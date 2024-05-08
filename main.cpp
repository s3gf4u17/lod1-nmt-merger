#include <fstream>
#include <string>
#include <filesystem>
#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polygon_mesh_processing/stitch_borders.h>
#include <CGAL/Polygon_mesh_processing/transform.h>
#include <CGAL/Polygon_mesh_processing/clip.h>
#include <CGAL/Aff_transformation_3.h>
#include <CGAL/boost/graph/IO/OBJ.h>
#include <CGAL/Surface_mesh.h>
typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Surface_mesh<Kernel::Point_3> Mesh;

int main(int argc,char **argv) {
    // 1. load nmt file
    Mesh NMTmerged,NMTcutter;
    std::ifstream inputNMT(argv[1]);
    CGAL::IO::read_OBJ(inputNMT,NMTmerged);
    inputNMT.clear();
    inputNMT.seekg(0);
    CGAL::IO::read_OBJ(inputNMT,NMTcutter);
    std::clog << "NMTmerged:" << NMTmerged.number_of_vertices() << "v" << NMTmerged.number_of_faces() << "f\t";
    std::clog << "NMTcutter:" << NMTcutter.number_of_vertices() << "v" << NMTcutter.number_of_faces() << "f\n";
    // 2. find translation vector
    Mesh::Vertex_index vi=*(NMTmerged.vertices_begin());
    Kernel::Point_3 tv=NMTmerged.point(vi);
    // 3. translate nmt
    CGAL::Polygon_mesh_processing::transform(CGAL::Aff_transformation_3<Kernel>(CGAL::Translation(),Kernel::Vector_3(-tv.x(),-tv.y(),-tv.z())),NMTmerged);
    CGAL::Polygon_mesh_processing::transform(CGAL::Aff_transformation_3<Kernel>(CGAL::Translation(),Kernel::Vector_3(-tv.x(),-tv.y(),-tv.z())),NMTcutter);
    // 4. reverse normals
    CGAL::Polygon_mesh_processing::reverse_face_orientations(NMTmerged);
    CGAL::Polygon_mesh_processing::reverse_face_orientations(NMTcutter);
    // 5. find prepared building objs
    for (const auto &file : std::filesystem::directory_iterator(argv[2])) {
        // 6. load buildings
        Mesh GMLmerger,GMLcutter;
        std::ifstream inputGML(file.path());
        CGAL::IO::read_OBJ(inputGML,GMLmerger);
        inputGML.clear();
        inputGML.seekg(0);
        CGAL::IO::read_OBJ(inputGML,GMLcutter);
        std::clog << "GMLmerger:" << GMLmerger.number_of_vertices() << "v" << GMLmerger.number_of_faces() << "f\t";
        std::clog << "GMLcutter:" << GMLcutter.number_of_vertices() << "v" << GMLcutter.number_of_faces() << "f\n";
        // 7. translate buildings
        CGAL::Polygon_mesh_processing::transform(CGAL::Aff_transformation_3<Kernel>(CGAL::Translation(),Kernel::Vector_3(-tv.x(),-tv.y(),-tv.z())),GMLmerger);
        CGAL::Polygon_mesh_processing::transform(CGAL::Aff_transformation_3<Kernel>(CGAL::Translation(),Kernel::Vector_3(-tv.x(),-tv.y(),-tv.z())),GMLcutter);
        // 8. reverse normals
        CGAL::Polygon_mesh_processing::reverse_face_orientations(GMLmerger);
        CGAL::Polygon_mesh_processing::reverse_face_orientations(GMLcutter);
        // 9. cut a hole in nmt
        CGAL::Polygon_mesh_processing::clip(NMTmerged,GMLcutter,CGAL::parameters::clip_volume(false));
        // 10. cut a hole in building
        CGAL::Polygon_mesh_processing::clip(GMLmerger,NMTcutter,CGAL::parameters::clip_volume(false));
        // 11. merge nmt with building
        NMTmerged+=GMLmerger;
        CGAL::Polygon_mesh_processing::stitch_borders(NMTmerged);
        // break;
    }
    // 11. export result
    std::ofstream result("result.obj");
    CGAL::IO::write_OBJ(result,NMTmerged);
    return 0;
}