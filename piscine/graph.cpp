#include "graph.h"
#include"grman\widget.h"
#include"time.h"
#include"fstream"
#include <sstream>

/***************************************************
                    VERTEX
****************************************************/

/// Le constructeur met en place les éléments de l'interface
VertexInterface::VertexInterface(std::string nom, int idx, int x, int y, int minim, int maxi ,std::string pic_name, int pic_idx)
{
    ///louis
    m_nom = nom;
    ///end louis

    // La boite englobante
    m_top_box.set_pos(x, y);
    m_top_box.set_dim(130, 100);
    m_top_box.set_moveable();

    // Le slider de réglage de valeur
    m_top_box.add_child( m_slider_value );
    m_slider_value.set_range(minim,maxi); // Valeurs arbitraires, à adapter...
    m_slider_value.set_dim(20,80);
    m_slider_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);

    // Label de visualisation de valeur
    m_top_box.add_child( m_label_value );
    m_label_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Down);

    // Une illustration...
    if (pic_name!="")
    {
        m_top_box.add_child( m_img );
        m_img.set_pic_name(pic_name);
        m_img.set_pic_idx(pic_idx);
        m_img.set_gravity_x(grman::GravityX::Right);
    }

    // Label de visualisation d'index du sommet dans une boite
    m_top_box.add_child( m_box_label_idx );
    m_box_label_idx.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Down);
    m_box_label_idx.set_dim(20,12);
    m_box_label_idx.set_bg_color(BLANC);

    m_box_label_idx.add_child( m_label_idx );
    m_label_idx.set_message( std::to_string(idx) );

    ///ajoute par louis
   /* ///ajout d'une box pour passer au graphe 2
    m_top_box.set_pos(x, y);
    m_top_box.set_dim(130, 100);
    m_top_box.set_moveable();*/
}


/// Gestion du Vertex avant l'appel à l'interface
void Vertex::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_value vers le slider associé
    m_interface->m_slider_value.set_value(m_value);

    /// Copier la valeur locale de la donnée m_value vers le label sous le slider
    m_interface->m_label_value.set_message( std::to_string( (int)m_value) );
}


/// Gestion du Vertex après l'appel à l'interface
void Vertex::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_value locale
    m_value = m_interface->m_slider_value.get_value();
}



/***************************************************
                    EDGE
****************************************************/

/// Le constructeur met en place les éléments de l'interface
EdgeInterface::EdgeInterface(Vertex& from, Vertex& to)
{
    // Le WidgetEdge de l'interface de l'arc
    if ( !(from.m_interface && to.m_interface) )
    {
        std::cerr << "Error creating EdgeInterface between vertices having no interface" << std::endl;
        throw "Bad EdgeInterface instanciation";
    }
    m_top_edge.attach_from(from.m_interface->m_top_box);
    m_top_edge.attach_to(to.m_interface->m_top_box);
    m_top_edge.reset_arrow_with_bullet();

    // Une boite pour englober les widgets de réglage associés
    m_top_edge.add_child(m_box_edge);
    m_box_edge.set_dim(24,60);
    m_box_edge.set_bg_color(BLANCBLEU);

    // Le slider de réglage de valeur
    m_box_edge.add_child( m_slider_weight );
    m_slider_weight.set_range(0,1000); // Valeurs arbitraires, à adapter...
    m_slider_weight.set_dim(16,40);
    m_slider_weight.set_gravity_y(grman::GravityY::Up);

    // Label de visualisation de valeur
    m_box_edge.add_child( m_label_weight );
    m_label_weight.set_gravity_y(grman::GravityY::Down);

}


/// Gestion du Edge avant l'appel à l'interface
void Edge::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_weight vers le slider associé
    m_interface->m_slider_weight.set_value(m_weight);

    /// Copier la valeur locale de la donnée m_weight vers le label sous le slider
    m_interface->m_label_weight.set_message( std::to_string( (int)m_weight ) );
}

/// Gestion du Edge après l'appel à l'interface
void Edge::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_weight locale
    m_weight = m_interface->m_slider_weight.get_value();
}



/***************************************************
                    GRAPH
****************************************************/

/// Ici le constructeur se contente de préparer un cadre d'accueil des
/// éléments qui seront ensuite ajoutés lors de la mise ne place du Graphe
GraphInterface::GraphInterface(int x, int y, int w, int h)
{
    m_top_box.set_dim(1000,740);
    m_top_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);

    m_main_box.add_child(m_tool_box);
    m_tool_box.set_dim(80,720);
    m_tool_box.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);
    m_tool_box.set_bg_color(BLEU);

    m_top_box.add_child(m_main_box);
    m_main_box.set_dim(908,720);
    m_main_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
    m_main_box.set_bg_color(BLANCJAUNE);

    ///ajoute par louis
    ///ajout d'une box pour passer au graphe 2
    m_tool_box.add_child(sauvegarde);
    sauvegarde.set_dim(50,60);
    sauvegarde.set_pos(2,3);
    sauvegarde.set_bg_color(BLANCBLEU);

    m_tool_box.add_child(graphe1);
    graphe1.set_dim(50,60);
    graphe1.set_pos(2,65);
    graphe1.set_bg_color(BLANCBLEU);

    m_tool_box.add_child(graphe2);
    graphe2.set_dim(50,60);
    graphe2.set_pos(2,127);
    graphe2.set_bg_color(BLANCBLEU);

}

///AJOUTE PAR LOUIS

double Vertex::getval()
{
    return m_value;
}
void Vertex::setval(double nouvelleval)
{
    m_value=nouvelleval;
}

void Graph::modifsommet()
{
    if(m_a == -1) m_a = m_vertices[0].getval();

    if(m_vertices[0].getval()!=m_a)
    {
//{
        m_vertices[1].setval(m_vertices[0].getval()*0.2);
        m_vertices[2].setval(m_vertices[1].getval()*0.15);

        m_a=-1;
    }
//}
}
/*double Graph::getvalue()
{
    return value;
}*/
/*void Graph::graphe1()
{
   /*Vertex plancton(100,nullptr);
   m_vertices[0]=plancton;
    Vertex poisson(50,nullptr);
    m_vertices[1]=poisson;
    Vertex pingouin(25,nullptr);
    m_vertices[2]=pingouin;
    Vertex lion_de_mer(10,nullptr);
    m_vertices[3]=lion_de_mer;
    Vertex orque(2,nullptr);
    m_vertices[4]=orque;

    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);
    // La ligne précédente est en gros équivalente à :
    // m_interface = new GraphInterface(50, 0, 750, 600);

    /// Les sommets doivent être définis avant les arcs
    // Ajouter le sommet d'indice 0 de valeur 30 en x=200 et y=100 avec l'image clown1.jpg etc...
    add_interfaced_vertex("plancton",0, 100.0, 200, 100,0,1000, "clown1.jpg");
    add_interfaced_vertex("poisson",1, 50.0, 400, 100,0,500, "clown2.jpg");
    add_interfaced_vertex("pingouin",2,  25.0, 200, 300,0,100, "clown3.jpg");
    add_interfaced_vertex("lion de mer",3,  10.0, 400, 300,0,50, "clown4.jpg");
    add_interfaced_vertex("orque",4,  2.0, 600, 300,0,25, "clown5.jpg");
    ///add_interfaced_vertex("autre",5,  0.0, 100, 500,0,1000, "bad_clowns_xx3xx.jpg", 0);
   /// add_interfaced_vertex("autre2",6,  0.0, 300, 500,0,1000, "bad_clowns_xx3xx.jpg", 1);
    ///add_interfaced_vertex("autre3",7,  0.0, 500, 500,0,1000, "bad_clowns_xx3xx.jpg", 2);

    ///pour afficher la valeur du poids du sommet
    ///std::cout<<m_vertices[0].getval();


    /// Les arcs doivent être définis entre des sommets qui existent !
    // AJouter l'arc d'indice 0, allant du sommet 1 au sommet 2 de poids 50 etc...
    add_interfaced_edge(0, 0, 1, 50.0);
    add_interfaced_edge(1, 1, 2, 50.0);
    add_interfaced_edge(2, 2, 3, 75.0);
    add_interfaced_edge(3, 3, 4, 25.0);
    add_interfaced_edge(4, 2, 4, 25.0);
    ///add_interfaced_edge(5, 7, 3, 25.0);
    ///add_interfaced_edge(6, 3, 4, 0.0);
    ///add_interfaced_edge(7, 2, 0, 100.0);
    ///add_interfaced_edge(8, 5, 2, 20.0);
    ///add_interfaced_edge(9, 3, 7, 80.0);

double a = m_vertices[0].getval();
while(m_vertices[0].getval()!=a)
{



        m_vertices[1].setval(m_vertices[0].getval()*3);
        std::cout<<m_vertices[1].getval();


}


}*/
/*void Graph::changeValSommet()
{
    double a=m_vertices[0].getval();

    if(m_vertices[0].getval()!=a)
    {
        m_vertices[1].setval(3);
        std::cout<<m_vertices[1].getval();
    }
}*/
/*void Graph::afficherPoidsSommet()
{

    while(m_vertices[0].getval()!=i)
{
    std::cout<<i<<std::endl;
    i=i+1;
}
}*/

/*void Graph::graphe2()
{
    std::map<int, Vertex> m_vertices2;
    Vertex voiture(100000,nullptr);
    m_vertices2[0]=voiture;
    Vertex forage_petrol(5,nullptr);
    m_vertices2[1]=forage_petrol;
    Vertex central_charbon(5,nullptr);
    m_vertices2[2]=central_charbon;
    Vertex central_nuc(2,nullptr);
    m_vertices2[3]=central_nuc;
    Vertex voiture_elec(100000,nullptr);
    m_vertices2[4]=voiture_elec;
    Vertex atmosphere(1000000,nullptr);
    m_vertices2[5]=atmosphere;


    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);
    // La ligne précédente est en gros équivalente à :
    // m_interface = new GraphInterface(50, 0, 750, 600);

    /// Les sommets doivent être définis avant les arcs
    // Ajouter le sommet d'indice 0 de valeur 30 en x=200 et y=100 avec l'image clown1.jpg etc...
    add_interfaced_vertex("voiture",0, 100000, 200, 100,0,100000, "clown1.jpg");
    add_interfaced_vertex("forage_petrol",1, 5, 400, 100,0,10, "clown2.jpg");
    add_interfaced_vertex("central_charbon",2,  5, 200, 300,0,10, "clown3.jpg");
    add_interfaced_vertex("central_nuc",3, 2, 400, 300,0,5, "clown4.jpg");
    add_interfaced_vertex("voiture_elec",4, 100000, 600, 300,0,100000, "clown5.jpg");
    add_interfaced_vertex("atmoqphere",5, 1000000, 100, 500,0,10000000, "bad_clowns_xx3xx.jpg", 0);
    ///add_interfaced_vertex(6,  0.0, 300, 500, "bad_clowns_xx3xx.jpg", 1);
    ///add_interfaced_vertex(7,  0.0, 500, 500, "bad_clowns_xx3xx.jpg", 2);

    /// Les arcs doivent être définis entre des sommets qui existent !
    // AJouter l'arc d'indice 0, allant du sommet 1 au sommet 2 de poids 50 etc...
    add_interfaced_edge(0, 0, 1, 50.0);
    add_interfaced_edge(1, 1, 2, 50.0);
    add_interfaced_edge(2, 2, 3, 75.0);
    add_interfaced_edge(3, 3, 4, 25.0);
    add_interfaced_edge(4, 2, 4, 25.0);
    ///add_interfaced_edge(5, 7, 3, 25.0);
    ///add_interfaced_edge(6, 3, 4, 0.0);
    ///add_interfaced_edge(7, 2, 0, 100.0);
    ///add_interfaced_edge(8, 5, 2, 20.0);
    ///add_interfaced_edge(9, 3, 7, 80.0);




}
/// Méthode spéciale qui construit un graphe arbitraire (démo)
/// Cette méthode est à enlever et remplacer par un système
/// de chargement de fichiers par exemple.
/// Bien sûr on ne veut pas que vos graphes soient construits
/// "à la main" dans le code comme ça.
void Graph::make_example()
{
    /*m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);
    // La ligne précédente est en gros équivalente à :
    // m_interface = new GraphInterface(50, 0, 750, 600);

    /// Les sommets doivent être définis avant les arcs
    // Ajouter le sommet d'indice 0 de valeur 30 en x=200 et y=100 avec l'image clown1.jpg etc...
    add_interfaced_vertex(0, 30.0, 200, 100, "clown1.jpg");
    add_interfaced_vertex(1, 60.0, 400, 100, "clown2.jpg");
    add_interfaced_vertex(2,  50.0, 200, 300, "clown3.jpg");
    add_interfaced_vertex(3,  0.0, 400, 300, "clown4.jpg");
    add_interfaced_vertex(4,  100.0, 600, 300, "clown5.jpg");
    add_interfaced_vertex(5,  0.0, 100, 500, "bad_clowns_xx3xx.jpg", 0);
    add_interfaced_vertex(6,  0.0, 300, 500, "bad_clowns_xx3xx.jpg", 1);
    add_interfaced_vertex(7,  0.0, 500, 500, "bad_clowns_xx3xx.jpg", 2);

    /// Les arcs doivent être définis entre des sommets qui existent !
    // AJouter l'arc d'indice 0, allant du sommet 1 au sommet 2 de poids 50 etc...
    add_interfaced_edge(0, 1, 2, 50.0);
    add_interfaced_edge(1, 0, 1, 50.0);
    add_interfaced_edge(2, 1, 3, 75.0);
    add_interfaced_edge(3, 4, 1, 25.0);
    add_interfaced_edge(4, 6, 3, 25.0);
    add_interfaced_edge(5, 7, 3, 25.0);
    add_interfaced_edge(6, 3, 4, 0.0);
    add_interfaced_edge(7, 2, 0, 100.0);
    add_interfaced_edge(8, 5, 2, 20.0);
    add_interfaced_edge(9, 3, 7, 80.0);
}*/

/// La méthode update à appeler dans la boucle de jeu pour les graphes avec interface
void Graph::update()
{
    if (!m_interface)
        return;

    for (auto &elt : m_vertices)
        elt.second.pre_update();

    for (auto &elt : m_edges)
        elt.second.pre_update();

    m_interface->m_top_box.update();

    for (auto &elt : m_vertices)
        elt.second.post_update();

    for (auto &elt : m_edges)
        elt.second.post_update();

}

/// Aide à l'ajout de sommets interfacés
void Graph::add_interfaced_vertex(std::string nom, int idx, double value, int x, int y, int minim, int maxi, std::string pic_name, int pic_idx)
{


    if ( m_vertices.find(idx)!=m_vertices.end() )
    {
        std::cerr << "Error adding vertex at idx=" << idx << " already used..." << std::endl;
        throw "Error adding vertex";
    }
    // Création d'une interface de sommet
    VertexInterface *vi = new VertexInterface(nom, idx, x, y, minim, maxi, pic_name, pic_idx);
    // Ajout de la top box de l'interface de sommet
    m_interface->m_main_box.add_child(vi->m_top_box);
    // On peut ajouter directement des vertices dans la map avec la notation crochet :
    m_vertices[idx] = Vertex(value, vi);
}

/// Aide à l'ajout d'arcs interfacés
void Graph::add_interfaced_edge(int idx, int id_vert1, int id_vert2, double weight)
{
    if ( m_edges.find(idx)!=m_edges.end() )
    {
        std::cerr << "Error adding edge at idx=" << idx << " already used..." << std::endl;
        throw "Error adding edge";
    }

    if ( m_vertices.find(id_vert1)==m_vertices.end() || m_vertices.find(id_vert2)==m_vertices.end() )
    {
        std::cerr << "Error adding edge idx=" << idx << " between vertices " << id_vert1 << " and " << id_vert2 << " not in m_vertices" << std::endl;
        throw "Error adding edge";
    }

    EdgeInterface *ei = new EdgeInterface(m_vertices[id_vert1], m_vertices[id_vert2]);
    m_interface->m_main_box.add_child(ei->m_top_edge);
    m_edges[idx] = Edge(weight, ei);
     /// OOOPS ! Prendre en compte l'arc ajouté dans la topologie du graphe !

    m_edges[idx].m_from = id_vert1;
    m_edges[idx].m_to = id_vert2;

    ///louis//////////
    m_vertices[id_vert1].m_out.push_back(idx);
    m_vertices[id_vert2].m_in.push_back(idx);
    ///End louis


///on donne id_vert2 en successeur à id_vert1
///et id_vert1 en prédécesseur à id_vert2

}

/// eidx index of edge to remove
void Graph::test_remove_edge(int eidx)
{
/// référence vers le Edge à enlever
Edge &remed=m_edges.at(eidx);

std::cout << "Removing edge " << eidx << " " << remed.m_from << "->" << remed.m_to << " " << remed.m_weight << std::endl;

/// Tester la cohérence : nombre d'arc entrants et sortants des sommets 1 et 2
std::cout << m_vertices[remed.m_from].m_in.size() << " " << m_vertices[remed.m_from].m_out.size() << std::endl;
std::cout << m_vertices[remed.m_to].m_in.size() << " " << m_vertices[remed.m_to].m_out.size() << std::endl;
std::cout << m_edges.size() << std::endl;

/// test : on a bien des éléments interfacés
if (m_interface && remed.m_interface)
{
/// Ne pas oublier qu'on a fait ça à l'ajout de l'arc :
/* EdgeInterface *ei = new EdgeInterface(m_vertices[id_vert1], m_vertices[id_vert2]); */
/* m_interface->m_main_box.add_child(ei->m_top_edge); */
/* m_edges[idx] = Edge(weight, ei); */
/// Le new EdgeInterface ne nécessite pas de delete car on a un shared_ptr
/// Le Edge ne nécessite pas non plus de delete car on n'a pas fait de new (sémantique par valeur)
/// mais il faut bien enlever le conteneur d'interface m_top_edge de l'arc de la main_box du graphe
m_interface->m_main_box.remove_child( remed.m_interface->m_top_edge );
}

/// Il reste encore à virer l'arc supprimé de la liste des entrants et sortants des 2 sommets to et from !
/// References sur les listes de edges des sommets from et to
std::vector<int> &vefrom = m_vertices[remed.m_from].m_out;
std::vector<int> &veto = m_vertices[remed.m_to].m_in;
vefrom.erase( std::remove( vefrom.begin(), vefrom.end(), eidx ), vefrom.end() );
veto.erase( std::remove( veto.begin(), veto.end(), eidx ), veto.end() );

/// Le Edge ne nécessite pas non plus de delete car on n'a pas fait de new (sémantique par valeur)
/// Il suffit donc de supprimer l'entrée de la map pour supprimer à la fois l'Edge et le EdgeInterface
/// mais malheureusement ceci n'enlevait pas automatiquement l'interface top_edge en tant que child de main_box !
m_edges.erase( eidx );

/// Tester la cohérence : nombre d'arc entrants et sortants des sommets 1 et 2
std::cout << m_vertices[remed.m_from].m_in.size() << " " << m_vertices[remed.m_from].m_out.size() << std::endl;
std::cout << m_vertices[remed.m_to].m_in.size() << " " << m_vertices[remed.m_to].m_out.size() << std::endl;
std::cout << m_edges.size() << std::endl;

}

///louis////////////

void Graph::CreateInterface()
{
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);
}

void Graph::Enregistrer(std::string fichier)
{
    std::ofstream outfile;

    outfile.open(fichier,std::ios::out | std::ios::trunc);

    outfile << m_vertexName << std::endl;
    for (auto& kv : m_vertices)
    {
        outfile << kv.first << " " ;
        kv.second.Print(outfile,m_separator,m_listSeparator);
        outfile << std::endl;
    }

    outfile << m_edgesName << std::endl;
    for (auto& kv : m_edges)
    {
        outfile << kv.first << " " ;
        PrintEdges(outfile,kv.second);
        outfile << std::endl;
    }

    ///TODO Ici on devra sauvegarder l'état du graphe pour la suite du projet (avec les évolutions du graphe jour après jour)

    outfile.close();
}

///pour charger un graphe
void Graph::Charger(std::string fichier)
{
    std::ifstream  input;
    input.open(fichier,std::ios::in);
    std::string elementLine;
    std::string categorie = "";
    int index = 0;
    int vertexMaxElement = 8;
    int edgeMaxElement = 4;
    std::string vertexValues[vertexMaxElement];
    std::string edgesValues[edgeMaxElement];

    while(std::getline(input,elementLine,'\n'))
    {
        std::istringstream  stream(elementLine);
        std::string element;
        while(std::getline(stream,element,m_separator))
        {
            if( element == m_vertexName || element == m_edgesName)
            {
                categorie = element;
            }

            if(categorie== m_vertexName && element != m_vertexName)
            {
                ///on a seulement 8 valeurs à gérer pour les sommets
                vertexValues[index] = element;
                if(index == vertexMaxElement-1)
                {
                    ///create the vertex
                    add_interfaced_vertex(vertexValues[1],std::stoi(vertexValues[0]),std::stod(vertexValues[2]),std::stoi(vertexValues[4]),std::stoi(vertexValues[5]),std::stoi(vertexValues[6]),std::stoi(vertexValues[7]),vertexValues[3]);
                }
                index = (index+1)%vertexMaxElement;
            }
            else if(categorie == m_edgesName && element != m_edgesName)
            {
                ///on a seulement 4 valeurs à gérer pour les edges
                edgesValues[index] = element;
                if(index == edgeMaxElement-1)
                {
                    ///create the edges
                    add_interfaced_edge(std::stoi(edgesValues[0]),std::stoi(edgesValues[1]),std::stoi(edgesValues[2]),std::stod(edgesValues[3]));
                }
                index = (index+1)%edgeMaxElement;
            }
        }
    }


    input.close();
}

void Vertex::Print(std::ofstream &stream,char separator,char secondarySeparator) const
{
    ///ecris le nom
    stream << m_interface->m_nom << separator;
    ///On n'ecris pas les index des arcs entrants/sortants

    ///Ecris le poids du noeud
    stream << m_value << separator;
    ///le chemin vers l'image
    stream << m_interface->m_img.get_pic_name() << separator;
    ///X et Y
    stream << m_interface->m_top_box.get_posx() << separator << m_interface->m_top_box.get_posy();

}

void Graph::PrintEdges(std::ofstream &outfile,const Edge & e)
{
    ///Ecris le poids du noeud
    outfile << e.m_from << m_separator << e.m_to << m_separator << e.m_weight;
}
///End louis////////

