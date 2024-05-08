> [!NOTE]  
> Jako iż wiem, że nie wszyscy mają ochotę na zabawę z Cmake'm, gotowy skompilowany program można znaleźć w zakładce Releases (po prawej stronie w GUI Githuba). BUILD JEDYNIE POD LINUXA.

### 1. Przekonwertować dane CityGML do formatu OBJ
- sklonować repozytorium https://github.com/tum-gis/CityGML2OBJv2
- w sklonowanym folderze zainstalować wymagane biblioteki, przykład:
```
sudo apt install virtualenv
virtualenv --python=python3 venv
source venv/bin/activate
pip install -r requirements.txt
```
- uruchomić konwerter komendą:
```
python3 CityGML2OBJs.py -i <folder-z-plikami-GML> -o <folder-do-zapisu> -g 1
```
### 2. Przygotować geometrię budynków
- załadowac plik .obj z poprzedniego etapu w programie [Blender](https://www.blender.org/)
- dla każdego z obiektów usunąć duplikaty werteksów poprzez:
    - kliknięcie na obiekt
    - "TAB" do przejścia w tryb edycji
    - "1" do przejścia w tryb werteksów
    - "A" do zaznaczenia wszystkich werteksów
    - prawy przycisk myszy -> merge vertices -> by distance
        - w lewym dolnym rogu ekranu ustawić distance na np 0.2m
- wyeksportować każdy z obiektów do nowego, wspólnego folderu
    - kliknięcie na obiekt
    - file->export->wavefront obj
        - limit to selected
        - forward -Z
        - up Y
        - +normals
        - +triangulated mesh
        - -materials export
### 3. Skompilować kod źródłowy
Program korzysta z zewnętrznych bibliotek. W folderze z kodem źródłowym należy utworzyć nowy folder `library`. Następnie pobrać odpowiednie wersje każdej z bibliotek: [boost-1.85.0](https://boostorg.jfrog.io/artifactory/main/release/1.85.0/source/boost_1_85_0.tar.gz), [CGAL-5.6](https://github.com/CGAL/cgal/releases/download/v5.6/CGAL-5.6-library.tar.xz), [eigen-3.4.0](https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.tar.gz). Po wypakowaniu drzewo plików powinno prezentować się mniej więcej tak:
```
library
├── boost_1_85_0
│   ├── boost
│   ├── doc
│   ├── libs
│   └── ...
├── CGAL-5.6
│   ├── auxiliary
│   ├── cmake
│   ├── data
│   └── ...
└── eigen-3.4.0
    ├── bench
    ├── blas
    ├── ci
    └── ...
```
Kompilacja wymaga instalacji dodatkowych pakietów:
```
sudo apt install libgmp-dev libmpfr-dev cmake -y
```
Następnie z wykorzystaniem narzędzia Cmake stworzyć folder `build` w którym wygenerowane zostaną pliki dla kompilatora:
```
cmake -DCGAL_DIR=library/CGAL-5.6 -DBOOST_ROOT=library/boost_1_85_0 -DEIGEN3_INCLUDE_DIR=library/eigen-3.4.0 -DCMAKE_BUILD_TYPE=Release -S . -B build
```
Ostatecznie, skompilować program:
```
cd build && make -j8
```
Program zostanie utworzony w lokalizacji `projekt/build/main`. Można go następnie przerzucić do dowolnego folderu jako samodzielny plik wykonywalny.
> [!WARNING]  
> W pliku `CMakeLists.txt` znajduje się również link do innej biblioteki - tinyxml2. Nie jest wymagane jej pobranie, linki zostały zakomentowane gdyż biblioteka nie została ostatecznie wykorzystana, ale może się przydać w przyszłości.
### 4. Uruchomić program
Przyotowane wcześniej budynki powinny znajdować się w oddzielnych plikach, w jednym folderze. Folder nie powinien zawierać innych plików. Przykład:
```
temp
├── ID-0464-2EE13F53-5D0A-10BF-E053-CA2BA8C063B3.obj
├── ID-0464-2EE13F53-5D07-10BF-E053-CA2BA8C063B3.obj
├── ID-0464-2EE13F53-63BA-10BF-E053-CA2BA8C063B3.obj
├── ID-0464-2EE13F53-64E4-10BF-E053-CA2BA8C063B3.obj
├── ID-0464-2EE13F53-64E5-10BF-E053-CA2BA8C063B3.obj
└── ID-0464-2EE13F53-6320-10BF-E053-CA2BA8C063B3.obj
```
Przykładowe dane zamieszczono razem w folderze `temp`. Program należy wywołać z dwoma dodatkowymi parametrami:
```
./main <sciezka-do-nmt-obj> <folder-z-budynkami-obj>
```
Wykorzystując jedynie dane zawarte w repozytorium komenda będzie wyglądać następująco:
```
./main ../data/nmt.obj ../temp
```
Wygenerowany zostanie plik `result.obj` z wynikiem połączenia geometrii NMT i CityGML. Z uwagi na to, że potraktowałem to jako zadanie czysto rekrutacyjne, nie dokładałem dodatkowych flag (np. do zmiany kierunku wektorów normalnych mesha). Na obecnym etapie takich zmian należy dokonywać w kodzie.
> [!WARNING]  
> Właśnie zauważyłem, że zapomniałem dodać translacji mesha do jego miejsca początkowego (pierwszy punkt nmt będzie zatem miał współrzędne 0,0,0 zamiast swoich wejściowych). Jest to dorzucenie 1 linijki kodu ale nie mam jak tego chwilowo zrobić gdyż jestem poza domem.