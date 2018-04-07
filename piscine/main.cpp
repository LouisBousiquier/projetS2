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
while ( !key[KEY_E] )
    {
    Graph g;
    Graph g2;
    Graph g3;
    ///g.graphe1();
    g.CreateInterface();

//g2.CreateInterface();
     if(mouse_b&1 && (mouse_x<140 && mouse_x>90)&&(mouse_y<139 &&mouse_y>79))
    {
        g2.CreateInterface();
        g2.Charger("Toto.txt");



    ///Louis


    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement à des frameworks plus avancés )
    while ( !key[KEY_ESC] )
    {

        /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
        g2.update();


        /// Mise à jour générale (clavier/souris/buffer etc...)
        grman::mettre_a_jour();

        ///pour enregistrer apres modification du graphe
        if(mouse_b&1 && (mouse_x<140 && mouse_x>90)&&(mouse_y<79 &&mouse_y>19))
            {
                g2.modifsommet();
                g2.Enregistrer("nouveaug1.txt");
            }
    }
}

    if(mouse_b&1 && (mouse_x<140 && mouse_x>90)&&(mouse_y<199 &&mouse_y>139))
    {
        g3.CreateInterface();
        g3.Charger("nouveau.txt");
        while ( !key[KEY_ESC] )
    {

        /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
        g3.update();


        /// Mise à jour générale (clavier/souris/buffer etc...)
        grman::mettre_a_jour();

        ///pour enregistrer apres modification du graphe
        if(mouse_b&1 && (mouse_x<140 && mouse_x>90)&&(mouse_y<79 &&mouse_y>19))
            {
                g3.modifsommet();
                g3.Enregistrer("nouveaug1.txt");
            }
    }
    }
    }



    grman::fermer_allegro();

    return 0;
}
END_OF_MAIN();


