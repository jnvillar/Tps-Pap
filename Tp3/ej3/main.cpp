#include "ej3.h"

/**
 * Modo de uso:
 *   Para usar con archivo de entrada: ./ej3 -i <archivo_entrada>
 *   Para usar por linea de comando:   ./ej3 -l
 */
int main(int argc, char *argv[]) {
  if (argc != 2 && argc != 3) {
    cout << "Modo de uso:\n";
    cout << "  Para usar con archivo de entrada: " << argv[0] << " -i <archivo_entrada>\n";
    cout << "  Para usar por linea de comando:   " << argv[0] << " -l \n";         
  } else {
    if (argc == 2 && !strcmp(argv[1], "-l"))
      resolverEjercicio("");
    else if (argc == 3 && !strcmp(argv[1], "-i"))
      resolverEjercicio(argv[2]);
    else {
      cout << "Ingresaste una combinacion invalida de opciones.\n";
      cout << "Modo de uso:\n";
      cout << "  Para usar con archivo de entrada: " << argv[0] << " -i <archivo_entrada>\n";
      cout << "  Para usar por linea de comando:   " << argv[0] << " -l \n";
    }
  }
  return 0;
}