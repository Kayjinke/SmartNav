cmake_minimum_required(VERSION 2.8)

find_package(FIDLGenerator)
find_package(FDEPLGenerator)

FIDLGenerate(HelloWorld.fidl)
FDEPLGenerate(depl/HelloWorld.fdepl)
FIDLGenerate(Navigation.fidl)
FDEPLGenerate(depl/Navigation.fdepl)

