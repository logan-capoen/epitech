#!/bin/bash
make re
# Chemins des dossiers
maps_dir="example_files/maps/"
solved_dir="example_files/solved/"
program="./setting_up"

# Vérifier l'existence du programme
if [ ! -f "$program" ]; then
    echo "Le programme $program n'existe pas. Assurez-vous qu'il est compilé et dans le répertoire courant."
    exit 1
fi

# Initialisation des compteurs et de la liste des fichiers échoués
tests_success=0
tests_fail=0
failed_tests=()

# Parcourir chaque fichier dans le dossier maps
for map_file in "$maps_dir"/*; do
    # Extraire le nom du fichier
    filename=$(basename "$map_file")
    solved_file="$solved_dir/$filename"

    # Vérifier si le fichier correspondant existe dans le dossier solved
    if [ ! -f "$solved_file" ]; then
        echo "Fichier correspondant manquant : $solved_file"
        continue
    fi

    # Exécuter le programme et comparer la sortie avec le fichier solved
    output=$("$program" "$map_file")
    expected_output=$(cat "$solved_file")

    if [ "$output" == "$expected_output" ]; then
        echo "Test réussi pour $filename"
        ((tests_success++))
    else
        echo "Test échoué pour $filename"
        ((tests_fail++))
        failed_tests+=("$filename")
        echo "Sortie attendue :"
        echo "$expected_output"
        echo "Sortie obtenue :"
        echo "$output"
    fi
done

# Afficher le résumé des tests
echo ""
echo "Résumé des tests :"
echo "Nombre de tests réussis : $tests_success"
echo "Nombre de tests échoués : $tests_fail"

# Afficher la liste des tests échoués s'il y en a
if [ ${#failed_tests[@]} -gt 0 ]; then
    echo ""
    echo "Liste des tests échoués :"
    for test in "${failed_tests[@]}"; do
        echo "- $test"
    done
fi
