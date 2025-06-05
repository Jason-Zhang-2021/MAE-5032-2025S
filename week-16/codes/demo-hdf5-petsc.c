#include <stdio.h>
#include <stdlib.h>
#include <hdf5.h>
#include <petscsys.h>
#include <petscviewerhdf5.h>

#define FILE "SDS.h5"

int main(int argc, char **argv) 
{
  PetscInitialize(&argc, &argv, NULL, NULL);

  int myparam1 = -1, myparam2 = -1;
  PetscBool flg1, flg2;

  // Read PETSc options from command line
  PetscOptionsGetInt(NULL, NULL, "-myparam1", &myparam1, &flg1);
  PetscOptionsGetInt(NULL, NULL, "-myparam2", &myparam2, &flg2);

  hid_t file_id, dataset_id;
  herr_t status;
  int i, j, k, dset_data[5][6][4];
  int *vec1 = (int *)malloc(5 * 6 * 4 * sizeof(int));

  file_id    = H5Fopen(FILE, H5F_ACC_RDWR, H5P_DEFAULT);
  dataset_id = H5Dopen(file_id, "/IntArray", H5P_DEFAULT);

  status = H5Dread(dataset_id, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, dset_data);
  printf("read from h5 dset_data[3][1][2]: %2d\n", dset_data[3][1][2]);

  status = H5Dread(dataset_id, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, vec1);
  printf("vec1(3,1,2): %2d\n", vec1[6 * 4 * 3 + 4 * 1 + 2]);

  for (j = 0; j < 5; j++) 
  {
    for (i = 0; i < 6; i++) 
    {
      for (k = 0; k < 4; k++)
        dset_data[j][i][k] = 200 + 100 * j + 10 * i + k;
    }
  }

  status = H5Dwrite(dataset_id, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, dset_data);
  status = H5Dread(dataset_id, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, dset_data);
  printf("updated dset_data[3][1][2]: %2d\n", dset_data[3][1][2]);

  // Create a group and dataset for PETSc parameters
  hid_t group_id = H5Gcreate(file_id, "/PETScParams", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

  hsize_t dims = 2;
  hid_t dataspace_id = H5Screate_simple(1, &dims, NULL);
  hid_t dset_id = H5Dcreate(group_id, "int_params", H5T_NATIVE_INT, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

  int petsc_params[2] = {myparam1, myparam2};
  status = H5Dwrite(dset_id, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, petsc_params);

  free(vec1);
  H5Dclose(dset_id);
  H5Sclose(dataspace_id);
  H5Gclose(group_id);
  H5Dclose(dataset_id);
  H5Fclose(file_id);

  PetscFinalize(); 
  return 0;
}

// EOF
