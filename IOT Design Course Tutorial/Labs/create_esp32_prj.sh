# clone esp32-vscode-project-template.git project 
# Add the code at the end of the .bashrc file 
esp32-new-project() {
if [ -z "$1" ]; then 
  echo "Error: add the name of the project" >&2
  echo "Example:  esp32-new-prj-template <my_project>" >&2
else 
  if [ ! -d "$1" ]; then
    git clone https://github.com/fmuller-pns/esp32-vscode-project-template.git
    rm -fR ./esp32-vscode-project-template/.git
    mv esp32-vscode-project-template $1
    cd $1
    echo "ESP32 project created: $1"
  else
    echo "Error: the $1 ESP32 project already exists!" >&2
  fi
fi
}
