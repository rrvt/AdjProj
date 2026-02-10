

AdjProj.chm : *.htm AdjProj.hhp AdjProj.hhc App.css
  -1 "C:\Program Files (x86)\HTML Help Workshop\hhc" AdjProj


Clean.cln    :
  @echo "Cleaning"
  cd $(MAKEDIR)
  if exist AdjProj.chm del /F AdjProj.chm


$(TgtFolder)/AdjProj.chm : AdjProj.chm
  copy $(MAKEDIR)\AdjProj.chm  $(MAKEDIR)\..\$(TgtFolder)\AdjProj.chm


$(TgtFolder)/Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\$(TgtFolder)
  if exist AdjProj.chm del /F AdjProj.chm
  cd $(MAKEDIR)


$(TgtFolder)/Rebuild.rbd : $(TgtFolder)/Clean.cln $(TgtFolder)/AdjProj.chm

