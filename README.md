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
    - prawy przycisk myszy -> merge vertices -> by distance (ustawić distance na np 0.2m)
- wyeksportowac kazdy z obiektow do nowego, wspolnego folderu (klikniecie na obiekt,file->export->wavefront obj:limit to selected,forward -Z,up Y,+normals,+triangulated mesh,-materials export)
3. skompilowac program
4. uruchomic program