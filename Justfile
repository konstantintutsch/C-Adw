[private]
default:
    just --list --justfile {{ justfile() }}

format:
    indent src/*.c src/*.h -linux -nut -i4

release:
    flatpak-builder --user --install --force-clean build/release build-aux/com.konstantintutsch.Template.yaml 

devel:
    flatpak-builder --user --install --force-clean build/devel build-aux/com.konstantintutsch.Template.Devel.yaml 

offline:
    flatpak-builder --user --install --force-clean --disable-download build/devel build-aux/com.konstantintutsch.Template.Devel.yaml 

setup:
    sudo dnf install -y indent
    sudo dnf install -y meson
    sudo dnf install -y flatpak-builder
    sudo dnf install -y libadwaita-devel
