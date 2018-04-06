#include "grman/grman.h"
#include <iostream>

#include "graph.h"

int main()
{
    /// A appeler en 1er avant d'instancier des objets graphiques etc...
    grman::init();

    /// Le nom du répertoire où se trouvent les images à charger
    grman::set_pictures_path("pics");

    /// Un exemple de graphe

    Graph g;
    ///g.graphe1();

    ///Louis
    g.CreateInterface();
    g.Charger("Toto.txt");


    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement à des frameworks plus avancés )
    while ( !key[KEY_ESC] )
    {

        /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
        g.update();


        /// Mise à jour générale (clavier/souris/buffer etc...)
        grman::mettre_a_jour();

        ///pour enregistrer apres modification du graphe
        if(mouse_b&1 && (mouse_x<188 && mouse_x>90)&&(mouse_y<110 &&mouse_y>19))
    {
        /*/// Il faut appeler les méthodes d'update des objets qui comportent des widgets
        g.update();

        /// Mise à jour générale (clavier/souris/buffer etc...)
        grman::mettre_a_jour();*/

        g.modifsommet();
        g.Enregistrer("nouveaug1.txt");


    }

    }


    grman::fermer_allegro();

    return 0;
}
END_OF_MAIN();


