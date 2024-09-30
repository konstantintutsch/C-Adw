#!/bin/bash

PROJECT_OLD_NAME=("template", "Template")
PROJECT_NEW_NAME=("", "")

printf "Project name [snake_case]: "
read PROJECT_NEW_NAME[0]
printf "Project name [CamelCase]: "
read PROJECT_NEW_NAME[1]

project_sed_name() {
    sed -i "s/${PROJECT_OLD_NAME[0]}/${PROJECT_NEW_NAME[0]}/g" "${1}"
    sed -i "s/${PROJECT_OLD_NAME[1]}/${PROJECT_NEW_NAME[1]}/g" "${1}"
}

PROJECT_OLD_ID="com.konstantintutsch.Template"
PROJECT_NEW_ID=""

printf "Project ID [com.konstantintutsch.Template]: "
read PROJECT_NEW_ID

project_sed_id() {
    sed -i "s/${PROJECT_OLD_ID}/${PROJECT_NEW_ID}/g" "${1}"
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
        project_sed_id "${file}"
        project_sed_name "${file}"
    done
done
# Left-over files
for file in "Justfile" "meson.build"
do
    project_sed_id "${file}"
    project_sed_name "${file}"
done

# Reset git
rm --recursive --verbose --interactive=never .git
git init
