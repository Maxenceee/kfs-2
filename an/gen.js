const fs = require('fs');
const path = require('path');

// Récupération des arguments de la ligne de commande
const [,, fichierSource, nomVariable] = process.argv;

if (!fichierSource || !nomVariable) {
    console.error("Erreur : Paramètres manquants.");
    console.error("Usage : node convert.js <fichier_source> <nom_variable>");
    console.error("Exemple : node convert.js mon_perroquet.js PARROT");
    process.exit(1);
}

// 1. Lecture du fichier source
if (!fs.existsSync(fichierSource)) {
    console.error(`Erreur : Le fichier "${fichierSource}" n'existe pas.`);
    process.exit(1);
}

const fileContent = fs.readFileSync(fichierSource, 'utf8');

// 2. Extraction dynamique de toutes les frames situées entre les backticks ` ... `
const frameRegex = /`([\s\S]*?)`/g;
const listeFrames = [];
let match;

while ((match = frameRegex.exec(fileContent)) !== null) {
    listeFrames.push(match[1]);
}

if (listeFrames.length === 0) {
    console.error("Erreur : Aucune frame détectée entre des backticks (`) dans le fichier source.");
    process.exit(1);
}

// 3. Préparation des noms pour le code C
const prefixeMaj = nomVariable.toUpperCase(); // Ex: KNOT
const prefixeMin = nomVariable.toLowerCase(); // Ex: knot
const nomFichierSortie = `res/${prefixeMin}_frames.h`;

// 4. Traitement et conversion
const FRAME_HEIGHT = 25;
const FRAME_WIDTH = 80;
const attributVGA = 0x07; // Texte Blanc sur Fond Noir

const framesConverties = listeFrames.map((frameStr, index) => {
    let lines = frameStr.split('\n');
    
    // Nettoyage strict initial des sauts de ligne résiduels des backticks
    if (lines[0] === '') lines.shift();
    if (lines[lines.length - 1] === '') lines.pop();

    // Calcul du cropping dynamique basé sur la hauteur réelle de la frame
    const toRemove = lines.length - FRAME_HEIGHT;
    const removeTop = Math.floor(toRemove / 2);
    const removeBottom = toRemove - removeTop;

    const croppedLines = lines.slice(removeTop, lines.length - removeBottom);

    // Conversion en uint16_t VGA
    return croppedLines.map(line => {
        const vgaLine = [];
        
        for (let i = 0; i < line.length; i++) {
            vgaLine.push((attributVGA << 8) | line.charCodeAt(i));
        }
        
        while (vgaLine.length < FRAME_WIDTH) {
            vgaLine.push((attributVGA << 8) | 32); // Remplissage espaces (' ')
        }
        
        return vgaLine.slice(0, FRAME_WIDTH);
    });
});

// 5. Construction dynamique du fichier d'en-tête C (.h)
let cCode = `#ifndef ${prefixeMaj}_FRAMES_H\n#define ${prefixeMaj}_FRAMES_H\n\n`;
cCode += `#include "types.h"\n\n`;
cCode += `#define ${prefixeMaj}_FRAME_COUNT ${framesConverties.length}\n`;
cCode += `#define ${prefixeMaj}_HEIGHT      ${FRAME_HEIGHT}\n`;
cCode += `#define ${prefixeMaj}_WIDTH       ${FRAME_WIDTH}\n\n`;
cCode += `static const uint16_t ${prefixeMin}_frames[${prefixeMaj}_FRAME_COUNT][${prefixeMaj}_HEIGHT][${prefixeMaj}_WIDTH] = {\n`;

framesConverties.forEach((frame, fIndex) => {
    cCode += "    {\n";
    frame.forEach(row => {
        const hexRow = row.map(word => `0x${word.toString(16).toUpperCase().padStart(4, '0')}`);
        cCode += `        {${hexRow.join(', ')}},\n`;
    });
    cCode += fIndex === framesConverties.length - 1 ? "    }\n" : "    },\n";
});

cCode += "};\n\n#endif\n";

// 6. Écriture sur le disque
fs.writeFileSync(nomFichierSortie, cCode);
console.log(`\nSuccès ! ${framesConverties.length} frames extraites.`);
console.log(`Fichier généré : ${nomFichierSortie}`);