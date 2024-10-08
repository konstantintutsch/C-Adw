#!/bin/bash

#
# Name
#

PROJECT_OLD_NAME=("template" "Template" "TEMPLATE")
PROJECT_NEW_NAME=("" "" "")

printf "Project name [snake_case]: "
read PROJECT_NEW_NAME[0]
printf "Project name [CamelCase]: "
read PROJECT_NEW_NAME[1]
printf "Project name [UPPERCASE]: "
read PROJECT_NEW_NAME[2]

project_sed_name() {
    sed -i "s/${PROJECT_OLD_NAME[0]}/${PROJECT_NEW_NAME[0]}/g" "${1}"
    sed -i "s/${PROJECT_OLD_NAME[1]}/${PROJECT_NEW_NAME[1]}/g" "${1}"
    sed -i "s/${PROJECT_OLD_NAME[2]}/${PROJECT_NEW_NAME[2]}/g" "${1}"
    
    # Fix symbols
    sed -i "s/${PROJECT_NEW_NAME[0]} \\$/template \\$/g" "${1}" # template keyword in Blueprints
    sed -i "s/gtk_widget_init_${PROJECT_NEW_NAME[0]}/gtk_widget_init_template/g" "${1}" # GTK function
    sed -i "s/gtk_widget_class_set_${PROJECT_NEW_NAME[0]}_from_resource/gtk_widget_class_set_template_from_resource/g" "${1}" # GTK function
}

#
# Description
#

PROJECT_OLD_DESCRIPTION=("A simple template for LibAdwaita C applications" "<p>Start a new project using LibAdwaita and C easily with this template. This template provides a Meson configuration, a C application, blueprint files, desktop and appstream files, translations and much more!</p>")
PROJECT_NEW_DESCRIPTION=("" "" "")

printf "Project description [short]: "
read PROJECT_NEW_DESCRIPTION[0]
printf "Project description [long]: "
read PROJECT_NEW_DESCRIPTION[1]

# Long description contains tags
PROJECT_OLD_DESCRIPTION[1]="${PROJECT_OLD_DESCRIPTION[1]//\//\\\/}"
PROJECT_NEW_DESCRIPTION[1]="${PROJECT_NEW_DESCRIPTION[1]//\//\\\/}"

project_sed_description() {
    sed -i "s/${PROJECT_OLD_DESCRIPTION[0]}/${PROJECT_NEW_DESCRIPTION[0]}/g" "${1}"
    sed -i "s/${PROJECT_OLD_DESCRIPTION[1]}/${PROJECT_NEW_DESCRIPTION[1]}/g" "${1}"
}

#
# ID
#
 
PROJECT_OLD_ID="com.konstantintutsch.Template"
PROJECT_NEW_ID=""

printf "Project ID [com.konstantintutsch.Template]: "
read PROJECT_NEW_ID

project_sed_id() {
    sed -i "s/${PROJECT_OLD_ID}/${PROJECT_NEW_ID}/g" "${1}"
}

#
# VCS URL
#

PROJECT_OLD_VCS_URL=("https://github.com/konstantintutsch/c-adw-template" "https://github.com/konstantintutsch/c-adw-template")
PROJECT_NEW_VCS_URL=("" "")

printf "Project VCS URL [${PROJECT_OLD_VCS_URL[0]}]: "
read PROJECT_NEW_VCS_URL[0]
printf "Project RAW VCS URL [${PROJECT_OLD_VCS_URL[1]}]: "
read PROJECT_NEW_VCS_URL[1]

PROJECT_OLD_VCS_URL[0]="${PROJECT_OLD_VCS_URL[0]//\//\\\/}"
PROJECT_NEW_VCS_URL[0]="${PROJECT_NEW_VCS_URL[0]//\//\\\/}"
PROJECT_OLD_VCS_URL[1]="${PROJECT_OLD_VCS_URL[1]//\//\\\/}"
PROJECT_NEW_VCS_URL[1]="${PROJECT_NEW_VCS_URL[1]//\//\\\/}"

project_sed_vcs_url() {
    sed -i "s/${PROJECT_OLD_VCS_URL[0]}/${PROJECT_NEW_VCS_URL[0]}/g" "${1}"
    sed -i "s/${PROJECT_OLD_VCS_URL[1]}/${PROJECT_NEW_VCS_URL[1]}/g" "${1}"
}

#
# Meta
#

project_sed() {
    project_sed_id "${1}"
    project_sed_vcs_url "${1}"
    project_sed_description "${1}"
    project_sed_name "${1}"
}

# Apply updates
for directory in "build-aux" "data" "po" "src"
do
    for file in $(find ${directory} -name "*${PROJECT_OLD_ID}*")
    do
        mv --verbose "${file}" "${file//$PROJECT_OLD_ID/$PROJECT_NEW_ID}"
    done

    for file in $(find ${directory} -type f)
    do
        project_sed "${file}"
    done
done
# Left-over files
for file in "Justfile" "meson.build" "README.md"
do
    project_sed "${file}"
done

README_INSTRUCTIONS="
To configure this template, run:

```xml
./template.sh
```
"
README_INSTRUCTIONS="${README_INSTRUCTIONS//\//\\\/}"
sed -i "s/${README_INSTRUCTIONS}//g" "README.md"

# Reset git
rm --recursive --verbose --interactive=never .git
git init

# Update files
for file in "data/${PROJECT_NEW_ID}.desktop.in.in" "data/${PROJECT_NEW_ID}.metainfo.xml.in.in" "src/application.c"
do
    vim "${file}"
done

# Reset translations
rm --verbose --interactive=never po/*.po po/*.pot po/LINGUAS
touch po/LINGUAS

meson setup build
cd build
meson compile ${PROJECT_NEW_ID}-pot
cd ..
