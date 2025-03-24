#include "json_reader.h"
#include "printer.h"
#include "../libs/gov_dev/gov_dev.h"

int main()
{
  int count = 0;
  const char *name;

  Registro *registros = parse_json_file("src/assets/exemplo_20.ERMAUF", &count);

  print_registros(registros, count);

  free_registro(registros, count);

  name = get_state_name_by_abbr("AC");
  printf("Estado: %s\n", name);

  return 0;
}