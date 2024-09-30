config_h = configuration_data()

config_h.set('project_name', project_name)
config_h.set('project_id', project_id)
config_h.set('project_version', project_version)

config_h.set('gettext_package', gettext_package)
config_h.set('localedir', project_localedir)

conf = configure_file(
  input: 'config.h.in',
  output: 'config.h',
  configuration: config_h
)

src = files(
  'main.c',
  'application.c',
  'window.c',
  'answer.c'
)

exe = executable(
          project_name,
                   src,
   include_directories: [internal_inc],
          dependencies: [gtk_dep, adwaita_dep],
               install: true
)
