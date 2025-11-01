#!/bin/bash
#
# This script tests for changes in output when changing/refactoring.
#
TESTS_DIR=tests
GENOTYPE="$TESTS_DIR"/test.genotype.txt
LOCATION="$TESTS_DIR"/test.location.txt

REF="$TESTS_DIR"/ref_results
NEW="$TESTS_DIR"/new_results
OUTPUTS=(accept corr freqs mapinfo params probs)
ASSIGN_OUTPUTS=(Ind7)

REF_SCAT="./SCAT3_ref"
NEW_SCAT="./src/SCAT3"

if [ ! -f "$REF_SCAT" ]; then
    printf "Cannot find %s, please compile one by stashing " $REF_SCAT
    printf "your changes, compiling with \"make -C src\", and copying "
    printf "the resulting binary %s to %s\n" $NEW_SCAT $REF_SCAT
    exit 1
fi

if ! make -C src SCAT3; then
    echo "Compiling failed. Please fix errors before continuing..."
    exit 1
fi

rm -r $REF $NEW
mkdir -p $REF $NEW

$REF_SCAT -S 0 -A 7 7 $GENOTYPE $LOCATION $REF 2
$NEW_SCAT -S 0 -A 7 7 $GENOTYPE $LOCATION $NEW 2

for output in "${OUTPUTS[@]}"; do
    if ! diff $REF/Output_"$output" $NEW/Output_"$output"; then
        echo "Found differences in $output output..."
        exit 1
    fi
done
for ind in "${ASSIGN_OUTPUTS[@]}"; do
    if ! diff $REF/"$ind" $NEW/"$ind"; then
        echo "Found differences in assignment output for individual $ind..."
        exit 1
    fi
done

echo "Found no difference in output between $REF_SCAT and $NEW_SCAT"