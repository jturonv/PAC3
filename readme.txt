PART 1
=======
crear usuari a GitHub jturonv@uoc.edu
sudo apt-get install git
sudo apt-get install gitk
configurar usuari
    git config user.name Josep
    git config user.mail jturonv@uoc.edu
    $ git config core.editor "editor (ex. vim)"
    $ git config merge.tool "tool (ex. diff)"
git init
git add libsrc/filtres.c
git add libsrc/filtres.h
git status
git commit -m "primer commit"
git remote add origin http://github.com/jturonv/PAC3.git
http://github.com/jturonv/PAC3.git      (clonem el projecte dins la carpeta PAC3 dins el directori actual)

PART 2
=======
sudo apt-get install doxygen
doxygen -g configdoxy   per crear el fitxer de configuració
modifiquem nom projecte, versió, etc  exportacio HTML i LATEX  OPTIMIZE_OUTPUT_FOR_C  = YES    RECURSIVE    = YES  input i output
posem descripció a cada funció i accés ràpid a cada una
llançar index.html
git commit -m "segon commit, amb documentació"