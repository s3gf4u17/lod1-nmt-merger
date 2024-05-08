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
- dla każdego z obiektów usunąć duplikaty werteksów
    - kliknięcie na obiekt
    - "TAB" do przejscia w tryb edycji,"1" do przejscia w tryb werteksow,"A" do zaznaczenia wszystkich,prawy przycisk myszy->merge vertices->by distance,ustawic distance na np. 20cm
- wyeksportowac kazdy z obiektow do nowego, wspolnego folderu (klikniecie na obiekt,file->export->wavefront obj:limit to selected,forward -Z,up Y,+normals,+triangulated mesh,-materials export)
3. skompilowac program
4. uruchomic program