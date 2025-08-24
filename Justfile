[private]
default:
    just --list --justfile {{ justfile() }}

format:
    indent src/*.c src/*.h -linux -nut -i4 -l1024

translate:
    meson compile -C _meson com.konstantintutsch.Template-pot
    meson compile -C _meson com.konstantintutsch.Template-update-po

local:
    flatpak remote-add --user --if-not-exists flathub https://flathub.org/repo/flathub.flatpakrepo
    flatpak run org.flatpak.Builder --user --sandbox \
        --force-clean --ccache --install-deps-from=flathub \
        --repo=_repo builddir \
        com.konstantintutsch.Template.Devel.yaml
    flatpak remote-add --if-not-exists --user --no-gpg-verify \
        com-konstantintutsch-Template-Devel \
        file://$(pwd)/_repo
    flatpak install --user --reinstall --assumeyes \
        --include-sdk --include-debug \
        com.konstantintutsch.Template.Devel
    GTK_DEBUG=interactive flatpak run \
        com.konstantintutsch.Template.Devel

debug:
    flatpak-coredumpctl \
        -m $(coredumpctl list -1 --no-pager --no-legend | grep -oE 'CEST ([0-9]+)' | awk '{print $2}') \
        com.konstantintutsch.Template.Devel

setup:
    sudo dnf install -y indent
    sudo dnf install -y meson
    sudo dnf install -y libadwaita-devel
    flatpak install --user --assumeyes org.gnome.Platform//47
    flatpak install --user --assumeyes org.gnome.Sdk//47
    flatpak install --user --assumeyes org.flatpak.Builder
