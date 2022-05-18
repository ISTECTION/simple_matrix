Param (
    [Parameter(Mandatory=$false)]
        [switch] $doc=$false,

    [Parameter(Mandatory=$false)]
        [string] $build_path='build',

    [Parameter(Mandatory=$false)]
        [ValidateSet('MinGW','default')] $compile='default'
)

if (Test-Path -Path $build_path) {
    Remove-Item -Force -Recurse -Path $build_path }
New-Item -Path $build_path -ItemType Directory

if($compile -eq 'MinGW') {
    cmake -G 'MinGW Makefiles' -S . -B $build_path
} else {
    cmake -S . -B $build_path
}
cmake --build $build_path