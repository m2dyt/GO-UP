#include <iostream>
#include <windows.h>
#include <osg/Geode>
#include <osg/ShapeDrawable>
#include <osg/Material>
#include <osg/Texture2D>
#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include <osg/Math>

using namespace std;

osg::Geode* createShapes() {
    osg::Geode* geode = new osg::Geode();
    osg::StateSet* stateset = new osg::StateSet();
    /*osg::Image* image = osgDB::readImageFile("Images/lz.rgb");
    if (image) {
        osg::Texture2D* texture = new osg::Texture2D;
        texture->setImage(image);
        stateset->setTextureAttributeAndModes(0, texture, osg::StateAttribute::ON);
    }*/

    geode->setStateSet(stateset);
    float radius = 0.8f;
    float height = 1.0f;
    osg::TessellationHints* hints = new osg::TessellationHints;
    hints->setDetailRatio(0.5f);
    geode->addDrawable(new osg::ShapeDrawable(new osg::Box(osg::Vec3(0.0f, 0.0f, 0.0f), 2 * radius), hints));
    geode->addDrawable(new osg::ShapeDrawable(new osg::Box(osg::Vec3(10.0f, 0.0f, 10.0f), 3 * radius), hints));
    geode->addDrawable(new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(9.0f, -4.0f, 0.0f), 2 * radius), hints));
    geode->addDrawable(new osg::ShapeDrawable(new osg::Cone(osg::Vec3(13.0f, 5.0f, 0.0f), 2 * radius, 6), hints));
    geode->addDrawable(new osg::ShapeDrawable(new osg::Cylinder(osg::Vec3(-1.0f, 5.0f, 8.0f), 1 * radius, 3), hints));
    geode->addDrawable(new osg::ShapeDrawable(new osg::Cylinder(osg::Vec3(-1.0f, 5.0f, 18.0f), 3 * radius, 4), hints));

    osg::HeightField* grid = new osg::HeightField;
    osg::Vec3 vec3 = { 6,-5,-2 };
    osg::Vec3 vec = { 1 ,1 ,1 };
    osg::Quat quat = { 30, vec };

    grid->setOrigin(vec3);
    grid->setRotation(quat);
    grid->allocate(38, 39);
    grid->setXInterval(0.28f);
    grid->setYInterval(0.28f);
    for (unsigned int r = 0; r < 39; ++r) {
        for (unsigned int c = 0; c < 38; ++c) {
            grid->setHeight(c, r, ((39 - r) + (38 - c)) / 4);
        }
    }
    geode->addDrawable(new osg::ShapeDrawable(grid));

    return geode;
}
int main(int, char**)
{
    // construct the viewer.
    osgViewer::Viewer viewer;
    // add model to viewer.
    viewer.setSceneData(createShapes());
    return viewer.run();

}
