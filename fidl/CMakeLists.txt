cmake_minimum_required(VERSION 2.8)

find_package(FIDLGenerator)
find_package(FDEPLGenerator)

FIDLGenerate(HelloWorld.fidl)
FDEPLGenerate(HelloWorld.fdepl)

FIDLGenerate(Navigation.fidl)
FDEPLGenerate(Navigation.fdepl)

#FIDLGenerate(DestinationInput.fidl)
#FDEPLGenerate(DestinationInput.fdepl)

