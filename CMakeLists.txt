# This exercise demonstrates a filter plugin.
cmake_minimum_required(VERSION 2.6)
  
FIND_PACKAGE(ParaView REQUIRED)
INCLUDE(${PARAVIEW_USE_FILE})

# Use the PLUGIN macro to create a plugin.
ADD_PARAVIEW_PLUGIN(TextGlyphs3D "1.0"
   SERVER_MANAGER_SOURCES TextGlyphs3D.cxx
   SERVER_MANAGER_XML TextGlyphs3D.xml)

