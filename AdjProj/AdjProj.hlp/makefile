

AdjProj.chm : *.htm AdjProj.hhp AdjProj.hhc App.css
  -1 "C:\Program Files (x86)\HTML Help Workshop\hhc" AdjProj


Clean.cln    :
  @echo "Cleaning"
  cd $(MAKEDIR)
  del /F AdjProj.chm


Release/AdjProj.chm : AdjProj.chm
  copy $(MAKEDIR)\AdjProj.chm  $(MAKEDIR)\..\Release\AdjProj.chm


Release/Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\Release
  del AdjProj.chm
  cd $(MAKEDIR)


Debug/AdjProj.chm : AdjProj.chm
  copy $(MAKEDIR)\AdjProj.chm  $(MAKEDIR)\..\Debug\AdjProj.chm


Debug/Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\Debug
  del AdjProj.chm
  cd $(MAKEDIR)


Release/Rebuild.rbd : Release/Clean.cln Release/AdjProj.chm


Debug/Rebuild.rbd   : Debug/Clean.cln Debug/AdjProj.chm


