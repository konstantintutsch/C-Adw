#
# Project
#

project(
     'Template',
            'c',
        version: '1.0.0',
        license: 'MIT',
  meson_version: '>= 1.4.1'
)
project_id = 'com.konstantintutsch.Template'

config_h = configuration_data()

flags = [
  '-DHAVE_CONFIG_H'
]

   project_prefix = get_option('prefix')
   project_bindir = project_prefix / get_option('bindir')
  project_datadir = project_prefix / get_option('datadir')
project_localedir = project_prefix / get_option('localedir')

macros = [
  ['PROJECT_NAME',    meson.project_name()],
  ['PROJECT_VERSION', meson.project_version()],
  ['PROJECT_ID',      project_id]
]

    gtk_dep = dependency('gtk4')
adwaita_dep = dependency('libadwaita-1', version: '>=1.4')

#
# Subdirectories
#

src = []

subdir('po')
subdir('src')

internal_inc = include_directories('.')

#
# Build
#

foreach macro: macros
  config_h.set_quoted(macro[0], macro[1])
endforeach

configure_file(
         output: 'config.h',
  configuration: config_h
)
configure_inc = include_directories('.')

exe = executable(
  meson.project_name(),
                   src,
   include_directories: [internal_inc, configure_inc],
          dependencies: [gtk_dep, adwaita_dep],
               install: true
)
