#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "dsexceptions.h"
#include <iostream> 
#include "EasyBMP.h"
#include <math.h>
#include "queue.cpp"
#include "utilities.cpp"
#include <vector>
using namespace std;

// AvlTree class
//
// CONSTRUCTION: with ITEM_NOT_FOUND object used to signal failed finds
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x (unimplemented)
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class AvlTree
{
  public:
    AvlTree( ) : root( NULL )
      { }
    AvlTree( const AvlTree & rhs ) : root( NULL )
    {
        *this = rhs;
    }

    ~AvlTree( )
    {
        makeEmpty( );
    }

    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException( );
        return findMin( root )->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMax( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException( );
        return findMax( root )->element;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains( const Comparable & x ) const
    {
        return contains( x, root );
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const
    {
        return root == NULL;
    }

	void setRadii(int orb,	int nod){
		orbit_radius = orb; node_radius = nod;}

    /**
     * Print the tree contents in sorted order.
     */
    void printTree() const
    {
        if( isEmpty( ) )
            cout << "Empty tree" << endl;
        else
            printTree( root );
    }
    
	//Overload public method to print a tree to a BMP file.
	void printTree(BMP& p)
    {
        
		if( isEmpty( ) )
            cout << "Empty tree" << endl;
        else {
            if(root->height == NULL)
			//If only one node exists 
				p.SetSize(orbit_radius*3, orbit_radius*3);
			else
				p.SetSize(root->height*orbit_radius*3, root->height*orbit_radius*3);
			
			
			visited = new bool*[p.TellWidth()];
			for(int k=0; k < p.TellWidth(); k++){
				visited[k] = new bool[p.TellHeight()];
				for(int j=0; j<p.TellHeight(); j++)
					//All points are not visited.
					visited[k][j] = false;
			}
			//Black
			RGBApixel color;
			color.Red=0;
			color.Blue=0;
			color.Green=0;
			
			//Call internal method
			printTree(p, root, root->height, 180.0, true,  p.TellWidth()/2, p.TellHeight()/2, 0, color);
			
			//Create each orbit
			setCircles(p);
			
		}
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( const Comparable & x , RGBApixel color)
    {
		insert( x, root, color );
    }

    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove( const Comparable & x )
    {
        cout << "Sorry, remove unimplemented; " << x <<
                " still present" << endl;
    }

    /**
     * Deep copy.
     */
    const AvlTree & operator=( const AvlTree & rhs )
    {
        if( this != &rhs )
        {
            makeEmpty( );
            root = clone( rhs.root );
        }
        return *this;
    }

  private:
    struct AvlNode
    {
        Comparable element;
        AvlNode   *left;
        AvlNode   *right;
        int       height;
		int		ring;
		RGBApixel color;

        AvlNode( const Comparable & theElement, AvlNode *lt,
                                                AvlNode *rt, int r, RGBApixel in_color,  int h = 0  )
          : element( theElement ), left( lt ), right( rt ), height( h ), ring( r ), color(in_color) 
		{ 
			//color.Blue = 0; color.Green = 0; color.Red = 255;
		}
    };

    AvlNode *root;
	int orbit_radius;
	int node_radius;
	bool** visited;

	//Method to create orbits on a BMP file
	void setCircles(BMP& p){
		AvlNode* temp = getRoot();
		
		//Grey
		RGBApixel ctemp;
		ctemp.Red=155;
		ctemp.Blue=155;
		ctemp.Green=155;

		for(int k=1; k<root->height+1; k++)
			drawCircle(p, p.TellWidth()/2, p.TellHeight()/2, orbit_radius*k, ctemp);
	}

	//Thank you wikipedia!
	void drawCircle(BMP& p, int x0, int y0, int radius, RGBApixel color)
	{
		int f = 1 - radius;
		int ddF_x = 1;
		int ddF_y = -2 * radius;
		int x = 0;
		int y = radius;

		setPixel(p, x0, y0 + radius,color);
		setPixel(p, x0, y0 + radius-1,color);
		setPixel(p, x0, y0 + radius+1,color);
		setPixel(p, x0+1, y0 + radius,color);
		setPixel(p, x0-1, y0 + radius,color);
		
		setPixel(p, x0, y0 - radius,color);
		setPixel(p, x0, y0 - radius+1,color);
		setPixel(p, x0, y0 - radius-1,color);
		setPixel(p, x0+1, y0 - radius,color);
		setPixel(p, x0-1, y0 - radius,color);
		
		setPixel(p, x0 + radius, y0,color);
		setPixel(p, x0 + radius+1, y0,color);
		setPixel(p, x0 + radius-1, y0,color);
		setPixel(p, x0 + radius, y0+1,color);
		setPixel(p, x0 + radius, y0-1,color);
		
		setPixel(p, x0 - radius, y0,color);
		setPixel(p, x0 - radius, y0+1,color);
		setPixel(p, x0 - radius, y0-1,color);
		setPixel(p, x0 - radius+1, y0,color);
		setPixel(p, x0 - radius-1, y0,color);
		
		while(x < y)
		{
			if(f >= 0) 
			{
				y--;
				ddF_y += 2;
				f += ddF_y;
			}
			x++;
			ddF_x += 2;
			f += ddF_x; 
		
			setPixel(p, x0 + x, y0 + y,color);
			setPixel(p, x0 + x+1, y0 + y,color);
			setPixel(p, x0 + x-1, y0 + y,color);
			setPixel(p, x0 + x, y0 + y+1,color);
			setPixel(p, x0 + x, y0 + y-1,color);
			
			
			setPixel(p, x0 - x, y0 + y,color);
			setPixel(p, x0 - x+1, y0 + y,color);
			setPixel(p, x0 - x-1, y0 + y,color);
			setPixel(p, x0 - x, y0 + y+1,color);
			setPixel(p, x0 - x, y0 + y-1,color);
		
			setPixel(p, x0 + x, y0 - y,color);
			setPixel(p, x0 + x+1, y0 - y,color);
			setPixel(p, x0 + x-1, y0 - y,color);
			setPixel(p, x0 + x, y0 - y+1,color);
			setPixel(p, x0 + x, y0 - y-1,color);
		
		
			setPixel(p, x0 - x, y0 - y,color);
			setPixel(p, x0 - x+1, y0 - y,color);
			setPixel(p, x0 - x-1, y0 - y,color);
			setPixel(p, x0 - x, y0 - y+1,color);
			setPixel(p, x0 - x, y0 - y-1,color);
		
		
			setPixel(p, x0 + y, y0 + x,color);
			setPixel(p, x0 + y+1, y0 + x,color);
			setPixel(p, x0 + y-1, y0 + x,color);
			setPixel(p, x0 + y, y0 + x+1,color);
			setPixel(p, x0 + y, y0 + x-1,color);
		
		
			setPixel(p, x0 - y, y0 + x,color);
			setPixel(p, x0 - y+1, y0 + x,color);
			setPixel(p, x0 - y-1, y0 + x,color);
			setPixel(p, x0 - y, y0 + x+1,color);
			setPixel(p, x0 - y, y0 + x-1,color);
		
		
			setPixel(p, x0 + y, y0 - x,color);
			setPixel(p, x0 + y+1, y0 - x,color);
			setPixel(p, x0 + y-1, y0 - x,color);
			setPixel(p, x0 + y, y0 - x+1,color);
			setPixel(p, x0 + y, y0 - x-1,color);
		
	
			setPixel(p, x0 - y, y0 - x,color);
			setPixel(p, x0 - y+1, y0 - x,color);
			setPixel(p, x0 - y-1, y0 - x,color);
			setPixel(p, x0 - y, y0 - x+1,color);
			setPixel(p, x0 - y, y0 - x-1,color);

		}	
	}

	//Thank you bresenham
	void drawLine(BMP& p, int x1, int y1, int x2, int y2, bool dashed, RGBApixel color)
	{
		dashed = false;
		double temp1, temp2;
		double slope = (y1-y2)/(x1-x2);
		if(x1>x2){
			int temp1 = x1;
			int temp2 = y1;
			x1=x2;
			y1=y2;
			x2=temp1;
			y2=temp2;
		}

		int dx  = x2 - x1;
		int dy  = y2 - y1;
		int y   = y1;
		int x	= x1;
		int eps = 0;
		if(slope < 1 && slope > -1)	
		{
			if(y2>y1)
			{
				for ( x = x1; x <= x2; x++ )  {
					if(!dashed){
						setPixel(p, x, y, color);
						setPixel(p, x+1, y, color);
						setPixel(p, x+1, y, color);
						setPixel(p, x, y-1, color);
						setPixel(p, x, y-1, color);
					}
					eps += dy;
					if ( (eps << 1) >= dx )  {
						y++;  eps -= dx;
					}
				}
			}
			else{
				for ( x = x1; x <= x2; x++ )  {
					if(!dashed){
						setPixel(p, x, y, color);
						setPixel(p, x+1, y, color);
						setPixel(p, x-1, y, color);
						setPixel(p, x, y+1, color);
						setPixel(p, x, y-1, color);
					}
					eps -= dy;
					if ( (eps << 1) >= dx )  {
						y--;  eps -= dx;
					}
				}
			}
		}
		else{
			if(y2>y1)
			{
				for ( y = y1; y <= y2; y++ )  {
					if(!dashed){
						setPixel(p, x, y, color);
						setPixel(p, x+1, y, color);
						setPixel(p, x-1, y, color);
						setPixel(p, x, y+1, color);
						setPixel(p, x, y-1, color);
					}
					eps += dx;
					int temp=0;
					if ( (temp = eps << 1) >= dy )  {
						x++;  eps -= dy;
					}
				}
			}
			else{
				for ( y = y1; y >= y2; y-- )  {
					if(!dashed){
						setPixel(p, x, y, color);
						setPixel(p, x+1, y, color);
						setPixel(p, x-1, y, color);
						setPixel(p, x, y+1, color);
						setPixel(p, x, y-1, color);
					}
					
					eps -= dx;
					if ( (eps << 1) <= dy )  {
						x++;  eps -= dy;
					}
				}
			}
		}
	}

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( const Comparable & x, AvlNode * & t , RGBApixel color)
    {
        if( t == NULL )
            t = new AvlNode( x, NULL, NULL, 0 , color);
        else if( x < t->element )
        {
            insert( x, t->left, color );
            if( height( t->left ) - height( t->right ) == 2 )
                if( x < t->left->element )
                    rotateWithLeftChild( t );
                else
                    doubleWithLeftChild( t );
        }
        else if( t->element < x )
        {
            insert( x, t->right, color );
            if( height( t->right ) - height( t->left ) == 2 )
                if( t->right->element < x )
                    rotateWithRightChild( t );
                else
                    doubleWithRightChild( t );
        }
        else
            ;  // Duplicate; do nothing
        t->height = max( height( t->left ), height( t->right ) ) + 1;
    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    AvlNode * findMin( AvlNode *t ) const
    {
        if( t == NULL )
            return NULL;
        if( t->left == NULL )
            return t;
        return findMin( t->left );
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    AvlNode * findMax( AvlNode *t ) const
    {
        if( t != NULL )
            while( t->right != NULL )
                t = t->right;
        return t;
    }


    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the tree.
     */
    bool contains( const Comparable & x, AvlNode *t ) const
    {
        if( t == NULL )
            return false;
        else if( x < t->element )
            return contains( x, t->left );
        else if( t->element < x )
            return contains( x, t->right );
        else
            return true;    // Match
    }

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty( AvlNode * & t )
    {
        if( t != NULL )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = NULL;
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void printTree( AvlNode *t ) const
    {
        if( t != NULL )
        {
            printTree( t->left );
            cout << t->element << endl;
            printTree( t->right );
        }
    }

	//Internal method to draw nodes on a BMP file
	//Parameters: BMP file, Node pointer, max height to the three, the degree of the last node with respect to
	//the origion, a bool to determin the last vector, the parent node's cordanents, what orbit the node should
	//be on
	//sign = true is positive; sign = false is negitive
	void printTree(BMP& p, AvlNode *t, int maxHeight, double degree, bool sign, int parentX, int parentY, int level, RGBApixel color)
    {
		static double PI = 3.14159265;
		
		double o,y,u,i;
		
		double tempx = parentX;
		double tempy = parentY;
		o = parentX;
		y = parentY;
		
		string filename;
		string output = "output";
		static int number = 0;
		string filetype = ".bmp";
		stringstream ss;


		if( t != NULL )
        {
			if(t->height == maxHeight){
				drawCircle(p, p.TellHeight()/2, p.TellWidth()/2, node_radius, color);
				fillCircle(p, p.TellWidth()/2, p.TellHeight()/2, t->color);	
				
				//Used to visualize the building of one tree
				/*ss << output << number++ << filetype;
				p.WriteToFile(ss.str().c_str());
				ss.str("");*/
				
				printTree(p, t->right, maxHeight, 0, true, (int)tempx, (int)tempy, level+1, color);
				printTree(p, t->left, maxHeight, 0, false, (int)tempx, (int)tempy, level+1, color);
				return;
			}
			else{
				tempx = p.TellWidth()/2;
				tempy = p.TellHeight()/2;
				if(sign){
					degree += 90/pow(2.0,level-1);
					if(degree==0)
						degree=90;
					o += sin(degree*PI/180)*node_radius;
					y -= cos(degree*PI/180)*node_radius;
					
					tempx += sin(degree*PI/180)*(orbit_radius*level);
					tempy -= cos((degree*PI)/180.0)*(orbit_radius*level);
					
					u = tempx;
					i = tempy;
					u += sin(-degree*PI/180)*node_radius;
					i += cos((-degree)*PI/180)*node_radius;
					
					drawCircle(p,(int)tempx, (int)tempy , node_radius, color);
					drawLine(p, o, y, u, i, false, color);
					fillCircle(p, (int)tempx, (int)tempy, t->color);
					
					//Used to visualize the building of one tree
					/*ss << output << number++ << filetype;
					p.WriteToFile(ss.str().c_str());
					ss.str("");
				*/
					//Draw line to center of circle
					//drawLine(p, parentX, parentY, tempx, tempy);
				
				}
				else{
					degree -= 90/pow(2.0,level-1);
					if(degree==0)
						degree=-90;

					o += sin(degree*PI/180)*node_radius;
					y -= cos(degree*PI/180)*node_radius;

					tempx += sin(degree*PI/180)*(orbit_radius*level);
					tempy -= cos((degree*PI)/180.0)*(orbit_radius*level);

					u = tempx;
					i = tempy;
					u += sin((360-(int)degree)%360*PI/180)*node_radius;
					i += cos((360-(int)degree)%360*PI/180)*node_radius;
				
					drawLine(p, o, y , u , i,false, color);
					drawCircle(p, (int)tempx, (int)tempy , node_radius, color);
					fillCircle(p, (int)tempx, (int)tempy, t->color);
					
					//Used to visualize the building of one tree
					/*ss << output << number++ << filetype;
					p.WriteToFile(ss.str().c_str());
					ss.str("");
				*/
					//draw line to center of cirle
					//drawLine(p, parentX, parentY, tempx, tempy);
				
				}
			}
			printTree(p, t->right, maxHeight, degree, true, (int)tempx, (int)tempy, level+1, color);
			printTree(p, t->left, maxHeight, degree, false, (int)tempx, (int)tempy, level+1, color);

        }
    }

	void fillCircle(BMP& p, int x, int y, RGBApixel color){
		queue Q;
		//vector<point> visited;
		point* tempPoint = new point(x,y);
		
	

		/*RGBApixel green;
		green.Green = 255;
		green.Red = 0;
		green.Blue = 0;*/
		Q.insert(tempPoint);
		while(!Q.isEmpty()){
			point current = Q.del();
			int currentx = current.getx();
			int currenty = current.gety();
			setPixel(p,currentx,currenty, color);
			//get the neighbors of the current pixel.
			neighborhood* tempHood = new neighborhood(p, current, WHITE);
			//test each of the neighbors
			for(int n=0; n<8; n++){
			//if a neighbor isn't null then it is a black pixel and put into the queue
				if(tempHood->neighbor[n] != NULL){
					int tempx = tempHood->neighbor[n]->getx();							
					int tempy = tempHood->neighbor[n]->gety();
					//if the pixel hasnt been visited insert it into the queue
					if(visited[tempx][tempy] != true){
						visited[tempx][tempy] = true;	
						Q.insert(tempHood->neighbor[n]);
					}
				}
			}	
		}
	}
    /**
     * Internal method to clone subtree.
     */
    AvlNode * clone( AvlNode *t ) const
    {
        if( t == NULL )
            return NULL;
        else
            return new AvlNode( t->element, clone( t->left ), clone( t->right ), t->height );
    }
        // Avl manipulations
    /**
     * Return the height of node t or -1 if NULL.
     */
    int height( AvlNode *t ) const
    {
        return t == NULL ? -1 : t->height;
    }

    int max( int lhs, int rhs ) const
    {
        return lhs > rhs ? lhs : rhs;
    }

    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then set new root.
     */
    void rotateWithLeftChild( AvlNode * & k2 )
    {
        AvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
        k1->height = max( height( k1->left ), k2->height ) + 1;
        k2 = k1;
    }

    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then set new root.
     */
    void rotateWithRightChild( AvlNode * & k1 )
    {
        AvlNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
        k2->height = max( height( k2->right ), k1->height ) + 1;
        k1 = k2;
    }

    /**
     * Double rotate binary tree node: first left child.
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then set new root.
     */
    void doubleWithLeftChild( AvlNode * & k3 )
    {
        rotateWithRightChild( k3->left );
        rotateWithLeftChild( k3 );
    }

    /**
     * Double rotate binary tree node: first right child.
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     */
    void doubleWithRightChild( AvlNode * & k1 )
    {
        rotateWithLeftChild( k1->right );
        rotateWithRightChild( k1 );
    }

    public:

	    /*static int height(AvlNode* t) {
	       // returns the height of the tree t
	      if (t == NULL) return -1;
	      else {
	            int p = height(t->left);
	            int q = height(t->right);
	            if (p < q)
	                 return 1+q;
	            else return 1 + p;

	     }
	    }
          */

	    static int size(AvlNode* t) {
	      if (t == NULL) return 0;
	      else
	         return 1 + size(t->left) + size(t->right);
	    }

	    AvlNode* getRoot() {
	      return root;
    }
};

#endif
