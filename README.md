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
python3 CityGML2OBJs.py -i <folder z plikami GML> -o <folder do zapisu> -g 1
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
Program korzysta z zewnętrznych bibliotek (boost/CGAL/eigen). W folderze z kodem źródłowym należy utworzyć nowy folder `library`. Następnie pobrać odpowiednie wersje każdej z bibliotek: [boost](), [CGAL](https://github.com/CGAL/cgal/releases/download/v5.6/CGAL-5.6-library.tar.xz), [eigen](https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.tar.gz)
4. uruchomic program