#!/usr/bin/env bash
set -euo pipefail

project_name='prog3_programacion_concurrente_v2026_2'
source_code=(
  include/clasificacion_numeros.h src/clasificacion_numeros.cpp
  include/suma_rangos.h src/suma_rangos.cpp
  include/suma_archivos.h src/suma_archivos.cpp
  include/frecuencia_numeros.h src/frecuencia_numeros.cpp
  include/cliente_bancario.h src/cliente_bancario.cpp
  include/logger.h src/logger.cpp
  include/productor_consumidor.h src/productor_consumidor.cpp
  include/lectura_ciclica.h src/lectura_ciclica.cpp
  include/sala.h src/sala.cpp
)
project_root="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
output_path="${project_root}/${project_name}.zip"

cd "${project_root}"
rm -f "${output_path}"
zip -r -S "${output_path}" "${source_code[@]}"
echo "Archivo generado: ${output_path}"
