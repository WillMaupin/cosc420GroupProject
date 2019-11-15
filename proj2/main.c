#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//print 'man' page for program
void manPage(){
    printf("Useage: mpiexec [executable] [tags <optional>] ... \n");
    printf("tag: -r || --read-files: read in files and create data structures\n");
    printf("tag: -h || --help: print user guide info\n");
}

//use MPI_File_read() to read files and ?create data structures?
/*
    NOTE:
        we could call this function twice, once for metadata file, again for
        cite data file, returning data read from each
        then use returned data in a seperate function called twice in a similar
        fashion...

        ill leave it as is for now, lmk what you think
*/
int readFiles(){
    //mpi stuff
    MPI_Init(NULL, NULL);
    MPI_Comm world = MPI_COMM_WORLD;
    int nprocs, rank;
    MPI_Comm_size(world, &nprocs);
    MPI_Comm_rank(world, &rank);

    char* cite_src = "./data/arxiv-citations.txt";
    char* meta_src = "./data/arxiv-metadata.txt";
    MPI_File meta_file, cite_file;  //not sure what these are for...

    //open files
    int meta_status = MPI_File_open(world, meta_src, MPI_MODE_RDONLY, MPI_INFO_NULL, &meta_file);
    int cite_status = MPI_File_open(world, cite_src, MPI_MODE_RDONLY, MPI_INFO_NULL, &cite_file);

    //check files were opened without issue
    if( meta_status || cite_status ){
        return 1;
    }



    //read meta_src
    MPI_File_seek(&meta_file, 0, MPI_SEEK_SET);
    //create structure for metadata
    //read_cite_src
    MPI_File_seek(&cite_file, 0, MPI_SEEK_SET);
    //create structure for citation data

    //close mpi files
    MPI_File_close(&meta_file);
    MPI_File_close(&cite_file);
    MPI_Finalize();
    return 0;
}


int main( int argc, char** argv ){
    //handle command line tags
    if( argc > 1 ){
        for( int i=1; i<argc; i++ ){    //start at 1 to skip exec file name
            if( strcmp(argv[i], "-r") == 0 || strcmp(argv[i], "--read-files") == 0 ){
                int read_status = readFiles();
                if( read_status ){
                    printf("Error: file read error\n");
                    exit(1);
                }else /*if( read_status == 0)*/{
                    printf("Read successful!\n");
                }
            }else if( strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0){
                manPage();
            }else if( strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--start") == 0 ){
                //execute using existing data structs, should enter UI mode
                printf("TODO: program should execute using existing data structures\n");
            }else{printf("Command \"%s\" not found!\n", argv[i]);}
        }
    }else{ printf("Useage: mpiexec [executable] [tags <optional>] ..."
                "\n\t(try -h or --help for more info)\n");}

    return 0;
}
