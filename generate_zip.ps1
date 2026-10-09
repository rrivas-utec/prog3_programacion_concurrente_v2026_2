[CmdletBinding()]
param()

$ErrorActionPreference = 'Stop'
$projectName = 'prog3_programacion_concurrente_v2026_2'
$sourceFiles = @(
    'include/clasificacion_numeros.h',
    'src/clasificacion_numeros.cpp',
    'include/suma_rangos.h',
    'src/suma_rangos.cpp',
    'include/suma_archivos.h',
    'src/suma_archivos.cpp',
    'include/frecuencia_numeros.h',
    'src/frecuencia_numeros.cpp',
    'include/cliente_bancario.h',
    'src/cliente_bancario.cpp',
    'include/logger.h',
    'src/logger.cpp',
    'include/productor_consumidor.h',
    'src/productor_consumidor.cpp',
    'include/lectura_ciclica.h',
    'src/lectura_ciclica.cpp',
    'include/sala.h',
    'src/sala.cpp'
)
$projectRoot = Split-Path -Parent $PSCommandPath
$outputPath = Join-Path $projectRoot "$projectName.zip"

foreach ($sourceFile in $sourceFiles) {
    if (-not (Test-Path -LiteralPath (Join-Path $projectRoot $sourceFile) -PathType Leaf)) {
        throw "No se encontro el archivo requerido: $sourceFile"
    }
}
if (Test-Path -LiteralPath $outputPath) { Remove-Item -LiteralPath $outputPath -Force }
Compress-Archive -LiteralPath ($sourceFiles | ForEach-Object { Join-Path $projectRoot $_ }) -DestinationPath $outputPath
Write-Host "Archivo generado: $outputPath"
