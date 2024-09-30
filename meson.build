#
# Project
#

project(
     'Template',
            'c',
        version: '1.0.0',
        license: 'MIT',
  meson_version: '>= 1.3'
)
base_id = 'com.konstantintutsch.Template'

profile = ''
id_suffix = ''
version_suffix = ''

if get_option('profile') == 'development'
  profile = 'devel'

  id_suffix = '.Devel'
  version_suffix = '-devel'
endif

project_name = meson.project_name()
project_id = base_id + id_suffix
project_version = meson.project_version() + version_suffix

project_prefix = get_option('prefix')
project_bindir = project_prefix / get_option('bindir')
project_datadir = project_prefix / get_option('datadir')
project_localedir = project_prefix / get_option('localedir')

gnome = import('gnome')

gtk_dep = dependency('gtk4')
adwaita_dep = dependency('libadwaita-1', version: '>=1.4')

#
# Subdirectories
#

internal_inc = include_directories('.')

subdir('po')
subdir('src')
