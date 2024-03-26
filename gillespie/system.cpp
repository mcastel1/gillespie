//
//  system.cpp
//  gillespie
//
//  Created by Michele on 07/02/2024.
//

#include "system.hpp"

inline SystemBits::SystemBits(void){
    
}

inline SystemBits::SystemBits(unsigned long long int N_in, unsigned int seed_in, const string& out_directory_in){
    
    
    unsigned int i, s, *n, n_bits_R;
    const double p[] = {1.0, 1.0, 2.0};
    
    
    n = new unsigned int [3];
    ran = gsl_rng_alloc(gsl_rng_gfsr4);
    
    gsl_rng_set(ran, seed);
    
    N = N_in;
    seed = seed_in;
    out_directory = out_directory_in;
    
    outfile_name.str("");
    outfile_name << out_directory << "/out_bits.dat";
    outfile.open(outfile_name.str().c_str());
    
    N_N_m_1_2 = N*(N-1)/2;

    
    //number of bits to write the random number (Fraction) R for the Gillespie simulation
    //VERIFY
    n_bits_R = bits((unsigned int)(gsl_pow_2(N)/3.0));
    //VERIFY
    
    for(x.clear(), /*c.clear(),*/ i=0; i<3; ++i){
        x.push_back(UnsignedInt(N));
    }
    x_t = x;
    
    //set a[i] so they can host the maximum values that can be stored in them
    for(a.resize(6), i=0; i<6; i++){
        a[i].Resize(2*x[0].GetSize());
    }
    


    L = UnsignedInt(N*(N-1)/2);
    R = UnsignedInt(N*(N-1)/2);
    w.resize(n_bits_R);
    
    //set x
    for(s=0; s<n_bits; s++){
        
        //draw the initial number of particles of the three species according to a multinomial distribution
        gsl_ran_multinomial(ran, 3, (unsigned int)N, p, n);
        
        for(i=0; i<3; ++i){
            
            //write the initial number of particles in x
            x[i].Set(s, n[i]);
              
        }
        
    }
    
//    x[0] -> A, x[1] -> L, x[2] -> D*
    
    //set a
    //set the first three values of a
    x[0].Multiply(&(x[2]), &(a[0]));
    x[0].Multiply(&(x[1]), &(a[1]));
    x[1].Multiply(&(x[2]), &(a[2]));
    
    //set the last three values
    x[0].Multiply(&(x[0]), &(a[3]));
    a[3].SubstractTo(&(x[0]), &borrow);
    a[3].DivideByTwoTo();

    x[2].Multiply(&(x[2]), &(a[4]));
    a[4].SubstractTo(&(x[2]), &borrow);
    a[4].DivideByTwoTo();

    x[1].Multiply(&(x[1]), &(a[5]));
    a[5].SubstractTo(&(x[1]), &borrow);
    a[5].DivideByTwoTo();


//
//    for(cout << "x[]: " << endl, i=0; i<x.size(); ++i){
//        cout << "x[" << i << "]" << endl;
//        x[i].PrintBase10("");
//    }
//    
//    
//    for(cout << "a[]:" << endl, i=0; i<a.size(); ++i){
//        cout << "a[" << i << "]" << endl;
//        a[i].PrintBase10("");
//    }

    
    delete [] n;
    
}

inline void SystemBits::Iterate(void){
    
    unsigned int i;
    
    //draw the random numbers
    r1 = gsl_rng_uniform(ran);
    tau = -1.0/((double)N_N_m_1_2)*log(r1);
    //the SetAll command here is a bottleneck
//    R.SetAll(gsl_rng_uniform_int(ran, N_N_m_1_2));
    R.SetAllToSize(gsl_rng_uniform_int(ran, N_N_m_1_2));
    //the SetAll command here is a bottleneck

    /*
     a0 = sum_{ a < b} x_a x_b + sum_a x_a(x_a-1)/2
        = 1/2 sum_{a!=b} x_a x_b + sum_a x_a(x_a-1)/2
        = 1/2 sum_{a!=b} x_a x_b + 1/2 sum_a x_a x_a - N/2
        = 1/2 sum_{a,b} x_a x_b - N/2
        = N^2/2 - N/2
        = N(N-1)/2
     */
    
//    R.PrintBase10("R");
//    
//    
////    for(cout << "x[]: " << endl, i=0; i<x.size(); ++i){
////        cout << "x[" << i << "]" << endl;
////        x[i].PrintBase10("");
////    }
//    
//    
//    for(cout << "a[]:" << endl, i=0; i<a.size(); ++i){
//        cout << "a[" << i << "]" << endl;
//        a[i].PrintBase10("");
//    }
//    
    //run through all reactions and compute the left-hand size of eq. (10b) in gillespie2007stochastic
    for (L.SetAll(0), compare_old.SetAll(true), i=0; i<3; i++) {
        
        
//        L.AddTo(&(a[i]), &carry);

        compare_new = (L < R);
        changer = (compare_old ^ compare_new);
        
//        L.PrintBase10("L");
//        compare_old.Print("compare_old");
//        compare_new.Print("compare_new");
//        changer.Print("changer");
        
//        x[0] -> A, x[1] -> L, x[2] -> D
        
        //I & x[0] and x[2] with changer and write the result in x_t[0] and x_t[2], respectively. The x_ts will be needed in the following no matter what i
        x[0].And(&changer, &(x_t[0]));
        x[1].And(&changer, &(x_t[2]));
        x[2].And(&changer, &(x_t[2]));
        
        //note that hwew the fourth, ..., sixth reaction are not considered because they don't do anything
        switch (i) {
                
            case 0:{
                //the first reaction A+D -> 2 D has been selected
                                
                //update the as
                
                //update a[0]
                //a[0] -> a[0] - x_D
                a[0].SubstractTo(&(x_t[2]), &borrow);
                //a[0] -> a[0] + x_A
                a[0].AddTo(&(x_t[0]), &carry);
                //a[0] -> a[0] -1
                a[0].SubstractTo(&changer, &borrow);
                
                //update a[1]
                //a[1] -> a[1] - x_L
                a[1].SubstractTo(&(x_t[1]), &borrow);
    
                //update a[2]
                //a[2] -> a[2] + x_L
                a[2].AddTo(&(x_t[1]), &carry);
                
                //update a[3]
                //a[3] -> a[3] - x_A
                a[3].SubstractTo(&(x_t[0]), &borrow);
                //a[3] -> a[3] + 1
                a[3].AddTo(&changer, &carry);
               
                //update a[4]
                //a[4] -> a[4] + x_D
                a[4].AddTo(&(x_t[2]), &carry);
 
                
                
                //update x
                x[0].SubstractTo(&changer, &borrow);
                x[2].AddTo(&changer, &carry);
                
                break;
                
            }
                
            case 1:{
                //the second reaction A+L -> 2 L  has been selected
            
                
                //update the as
                /*
                 a[0] = x[0]*x[2] -> (x[0]-changer)*x[2] = a[0] - changer*x[2] = a[0] - x_t[2]
                 a[1] = x[0]*x[1] -> (x[0]-changer)*(x[1]+changer) = a[0] - x_t[1] +x_t[0] - changer
                 a[2] = x[1]*x[2] -> (x[1]+changer)*x[2] = a[2] + x_t[2]
                 a[3] = x[0]*(x[0]-1)/2 -> (x[0]-changer)*(x[0]-1-changer)/2 = a[3] - x_t[0] + changer*(1+changer)/2 = a[3] - x_t[0] + changer
                 a[5] = x[1]*(x[1]-1)/2 -> (x[1]+changer)*(x[1]-1+changer)/2 = a[5] + changer*(x[1]-1)/2 + changer*x[1]/2 + changer/2 = a[5] + x_t[1]
                
                 */
                
                //update a[0]
                //a[0] -> a[0] - x_D
                a[0].SubstractTo(&(x_t[2]), &borrow);

                //update a[1]
                a[1].SubstractTo(&(x_t[1]), &borrow);
                a[1].AddTo(&(x_t[0]), &carry);
                a[1].SubstractTo(&changer, &borrow);

                //update a[2]
                a[2].AddTo(&(x_t[2]), &carry);

                //update a[3]
                a[3].SubstractTo(&(x_t[0]), &borrow);
                a[3].AddTo(&changer, &carry);

                //update a[5]
                a[5].AddTo(&(x_t[1]), &carry);

                
                
                //update x
                x[0].SubstractTo(&changer, &borrow);
                x[1].AddTo(&changer, &carry);
  
                break;
                
            }
                
            case 2:{
                //the third reaction D+L -> 2 A  has been selected
                
                //x[0]->x[0]+changer, x[1] -> x[1]-changer, x[2] -> x[2]-changer
                
                //update the as
                /*
                 a[0] = x[0]*x[2] -> (x[0]+changer)*(x[2]-changer) = a[0] + changer*x[2] - changer*x[0] - changer = a[0] + x_t[2] - x_t[0] - changer
                 a[1] = x[0]*x[1] -> (x[0]+changer)*(x[1]-changer) = a[1] + x_t[1] - x_t[0] - changer
                 a[2] = x[1]*x[2] -> (x[1]-changer)*(x[2]-changer) = a[2] - x_t[2] - x_t[1] + changer
                 a[3] = x[0]*(x[0]-1)/2 -> (x[0]+changer)*(x[0]-1+changer)/2 = a[3] + changer*(x[0]-1)/2 + changer*x[0]/2 + changer/2 = a[3] + x_t[0]
                 a[4] = x[2]*(x[2]-1)/2 -> (x[2]-changer)*(x[2]-1-changer)/2 = a[4] - changer*(x[2]-1)/2 - changer*x[2]/2 + changer/2 = a[4] - x_t[2] + changer
                 a[5] = x[1]*(x[1]-1)/2 -> (x[1]-changer)*(x[1]-1-changer)/2 = a[5] - changer*(x[1]-1)/2 - changer*x[1]/2 + changer/2 = a[5] - x_t[1] + changer

                 */
                //update a[0]
                a[0].AddTo(&(x_t[2]), &carry);
                a[0].SubstractTo(&(x_t[0]), &borrow);
                a[0].SubstractTo(&changer, &borrow);
                
                //update a[1]
                a[1].AddTo(&(x_t[1]), &carry);
                a[1].SubstractTo(&(x_t[0]), &borrow);
                a[1].SubstractTo(&changer, &borrow);

                //update a[2]
                a[2].SubstractTo(&(x_t[2]), &borrow);
                a[2].SubstractTo(&(x_t[1]), &borrow);
                a[2].AddTo(&changer, &carry);

                //update a[3]
                a[3].AddTo(&(x_t[0]), &carry);
                
                //update a[4]
                a[4].SubstractTo(&(x_t[2]), &borrow);
                a[4].AddTo(&changer, &carry);
                
                //update a[5]
                a[5].SubstractTo(&(x_t[1]), &borrow);
                a[5].AddTo(&changer, &carry);

                
                //update x
                x[2].SubstractTo(&changer, &borrow);
                x[1].SubstractTo(&changer, &borrow);
                x[0].AddTo(&changer, &carry);

                break;
                
            }

        }
        
        compare_old = compare_new;

    }

    
    //print simulation results
    x[0].Print(outfile);
    x[1].Print(outfile);
    x[2].Print(outfile);
    outfile << tau << endl;
    

    
}


inline systemnobits::systemnobits(void){
    
}


inline systemnobits::systemnobits(unsigned long long int N_in, unsigned int seed_in, const string& out_directory_in){
    
    unsigned int i, *n;
    const double p[] = {1.0, 1.0, 2.0};
    
    
    
    n = new unsigned int [3];
    ran = gsl_rng_alloc(gsl_rng_gfsr4);
    
    gsl_rng_set(ran, seed);
    
    N = N_in;
    seed = seed_in;
    out_directory = out_directory_in;
    
    outfile_name.str("");
    outfile_name << out_directory << "/out_nobits.dat";
    outfile.open(outfile_name.str().c_str());
    
    N_N_m_1_2 = N*(N-1)/2;
    
    x.resize(3);
    x_t.resize(3);
    //    c.resize(3);
    a.resize(3);
    
    
    
    //draw the initial number of particles of the three species according to a multinomial distribution
    gsl_ran_multinomial(ran, 3, (unsigned int)N, p, n);
    
    for(i=0; i<3; ++i){
        
        //write the initial number of particles in x
        x[i] = n[i];
        //draw the values of c and write them in c
        //        c[i] = (unsigned int)gsl_rng_uniform_int(ran, M);
        
    }
    
    a[0] = x[0]*x[2];
    a[1] = x[0]*x[1];
    a[2] = x[1]*x[2];
    a[3] = x[0]*(x[0]-1)/2;
    a[4] = x[2]*(x[2]-1)/2;
    a[5] = x[1]*(x[1]-1)/2;
    
    delete [] n;
    
}


inline void systemnobits::iterate(void){
    
    unsigned int i;
    
    //draw the random numbers
    r1 = gsl_rng_uniform(ran);
    tau = -1.0/((double)N_N_m_1_2)*log(r1);
    R = gsl_rng_uniform_int(ran, N_N_m_1_2);
    
    for (L=0, compare_old=true, i=0; i<3; i++) {
        
        L += a[i];
        
        compare_new = (L < R);
        changer = (compare_old ^ compare_new);
        
        x_t[0] = (changer ? x[0] : 0);
        x_t[1] = (changer ? x[1] : 0);
        x_t[2] = (changer ? x[2] : 0);
        
        switch (i) {
            case 0:{
                
                //update the as
                //update a[0]
                a[0]-=x_t[2];
                a[0]+=x_t[0];
                a[0]-=changer;
                
                //update a[1]
                a[1]-=x_t[1];
                
                //update a[2]
                a[2]+=x_t[1];
                
                //update a[3]
                a[3]-=x_t[0];
                a[3]+=changer;
                
                //update a[4]
                a[4]+=x_t[2];
                
                //update x
                x[0]-=changer;
                x[2]+=changer;
                
                break;
                
            }
                
            case 1:{
                //the second reaction A+L -> 2 L  has been selected
                
                //update the as
                a[0]-=x_t[2];
                
                a[1]-=x_t[1];
                a[1]+=x_t[0];
                a[1]-=changer;
         
                a[2]+=x_t[2];
                
                a[3]-=x_t[0];
                a[3]+=changer;
                
                a[5]+=x_t[1];
                
                
                //update x
                x[0]-=changer;
                x[1]+=changer;
  
                break;
                
            }
                
            case 2:{
                //the third reaction D+L -> 2 A  has been selected
                
                //update a
                a[0]+=x_t[2];
                a[0]-=x_t[0];
                a[0]-=changer;
                
                a[1]+=x_t[1];
                a[1]-=x_t[0];
                a[1]-=changer;
                
                a[2]-=x_t[2];
                a[2]-=x_t[1];
                a[2]+=changer;
                
                a[3]+=x_t[0];
                
                a[4]-=x_t[2];
                a[4]+=changer;
                
                a[5]-=x_t[1];
                a[5]+=changer;

                
                //update x
                x[2]-=changer;
                x[1]-=changer;
                //here A should be updated by 2 changer!
                x[0]+=changer;
                //here A should be updated by 2 changer!


                break;
                
            }

        }
                
        compare_old = compare_new;
        
    }
    
    outfile << x[0] << "\t" << x[1] << "\t" << x[2] << "\t" << tau << endl;
    
}
