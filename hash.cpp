#include<bits/stdc++.h>
#include<vector>
#include<exception>
#define FOR(i , n) for(int i=0 ; i< n ;i++)
#define LOOP(i , a , b) for(int i = a ; i <= b ; i++ )



using namespace std ;
vector<vector<int>*> directory ;
vector<vector<int>*> buckets ;

int power(int a  , int b)
{
    int ans =1 ;
    while(b--) ans *= a ;
    return ans ;
}

void clear_buckets ()
{
    int size = buckets.size();
    
    for(int i=0 ; i< size ; i++)
    {
        buckets[i] -> clear() ;
    }
}

void add_bucket ( int local_depth , int bucket_capacity  , int place , int push  )
{
        //vector<int>* p = new vector<int>() ;
        vector<int> vect ;  vector<int>* p = &vect ;  
      
         p->push_back(local_depth) ;
         if(push == 1) directory.push_back(p) ;
         else directory[place] = p ;

         buckets.push_back(p) ;
}

int insert (int x , int global_depth , int bucket_capacity )
{
                                                              //cout<<"tinggg"<<endl ;
    int size = power(2 , global_depth) ;                      //cout<<"global ,, size  "<<global_depth<<" "<<size<<endl ;
    int y = x%size ;                                          //cout<<"y   "<<y<<endl ;
    if( directory[y]->size() <= bucket_capacity )
    {
        directory[y]->push_back(x)   ; 
    }
    else 
    {
        if( directory[y] -> at(0) < global_depth )
        {
             directory[y] -> at(0) ++ ;                                                 //cout<<"here"<<endl ;
             int divider = power(2 , directory[y] -> at(0)) ;
             add_bucket( (directory[y] ->at(0)), bucket_capacity , y + (size/2) , 0) ;  //cout<<"new-bucket_added"<<endl ;
            
             for(auto itr = ( directory[y] -> begin()) + 1 ; itr != directory[y] -> end() ; ++itr )
             {
                 if(*itr / divider == 0 ) continue; 
                 else 
                 {
                     int temp = *itr ;
                     directory[y] -> erase(itr) ;
                     global_depth = insert(temp , global_depth , bucket_capacity) ;
                 }
             }
                   global_depth = insert(x , global_depth , bucket_capacity) ;
                   //cout<<"insertion done"<<endl ;
        }
        else
        {
            global_depth += 1 ;                                                   
            size = power(2 , global_depth) ;                                         //cout<<"size   "<<size<<endl ;
            //y = x%size ;                                                           cout<<"y   "<<y<<endl ;
            directory.resize(size) ;
            LOOP(i , size/2 , size-1) directory[i] = directory[i - (size/2) ] ;    //cout<<directory[y] ->at(0)<<endl ;  //cout<<"connected"<<endl; 

            //dividing the directory[y]
            directory[y] -> at(0)++ ;             //cout<<"eww"<<directory[y] -> at(0)<<endl ;             //cout<<"local depth   "<<directory[y] -> at(0)<<endl ;
            int divider = power(2 , directory[y] ->at(0)) ;  
            add_bucket( (directory[y] ->at(0)), bucket_capacity , y + (size/2) , 0) ;                    //cout<<"new-bucket_added"<<endl ;

            for(auto itr = ( directory[y] -> begin()) + 1 ; itr != directory[y] -> end() ; ++itr )
             {
        
                 if(*itr % divider == 0 ) { continue;} 
                 else 
                 {
                     int temp = *itr ;
                     directory[y] -> erase(itr) ;
                     directory[y + (size/2)] ->push_back(temp) ; 
                 }
             }
                                                                                                         //cout<<"divided"<<endl ;
             global_depth = insert(x , global_depth , bucket_capacity) ;
            

                                                                                                         //cout<<"insertion done "<<endl ;
            
             
        }
    }
    return global_depth ;
}

int search (int x , int global_depth  )
{
      int size = power(2 , global_depth) ;
      int y = x % size ;
      return y ;
}


void status (int global_depth )
   {
        cout<<global_depth<<endl ;
        cout<<buckets.size()<<endl ;
         FOR(i , buckets.size())
         {
             cout<<( buckets[i] -> size() ) -1<<" "<<buckets[i] -> at(0)<<endl ;
         }
   }

void delete_ (int x , int global_depth, int bucket_size)
{
    int size = power(2 , global_depth) ;
    int y = x%size ;
    for(auto itr = directory[y] -> begin() ; itr != directory[y] -> end() ; ++itr )
    {
        //if(directory[y] -> at(i) == x ) directory[y] -> erase(i) ;
        if( *itr == x ) {directory[y] -> erase(itr) ; return ;}
    }
    cout<<"not found"<<endl ;
}

int main()
{
    int global_depth , bucket_capacity , x ;

    cin>>global_depth>>bucket_capacity ;

    int size = power(2 , global_depth);
    
    
    FOR(i , size)
    {
        /*  int *p = (int*)malloc((bucket_capacity+2)*sizeof(int))  ;
        directory.push_back(p) ;
        *(p+size+1) = 0 ;
        *(p) = global_depth ;
         ;  */

        /* vector<int>* p = new vector<int>()  ;  
         p->resize(bucket_capacity + 2);
         p->at(0) = global_depth ;
         p->at(size+1) = 0 ;
         directory.push_back(p) ; */
        
        add_bucket (global_depth , bucket_capacity , 0 , 1 ) ;
 
    }



     while(cin>>x)
    {
      if(x == 2) //insert
      {
          //cout<<"inserting"<<endl ;
          cin>>x ; global_depth = insert(x , global_depth , bucket_capacity) ;
      }

     // else if(x == 3) //search 

       else if(x == 4) //delete 
       {
           cin>>x ; delete_(x , global_depth ,bucket_capacity) ;
       }

      else if(x == 5) //display status 
      status(global_depth ) ;

      else if(x == 6) { clear_buckets() ; break ;}
      else {clear_buckets() ;break ; }
    }  
}