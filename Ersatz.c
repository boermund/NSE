 int imax = 2, jmax = 6, i, j;
   /* Matrix ist Zeiger auf int-Zeiger. */

    float ** matrix;

 /* Speicher reservieren für die int-Zeiger (=zeile) */
   matrix = malloc(imax * sizeof(float*));
   if(NULL == matrix) {
      printf("Kein virtueller RAM mehr vorhanden ... !");
      return EXIT_FAILURE;
   }
   /* jetzt noch Speicher reservieren für die einzelnen Spalten
    * der i-ten Zeile */
   for(i = 0; i < imax; i++) {
      matrix[i] = malloc(jmax* sizeof(float));
         if(NULL == matrix[i]) {
            printf("Kein Speicher mehr fuer Zeile %d\n",i);
            return EXIT_FAILURE;
         }
   }

   /* Inhalt der Matrix entsprechend ausgeben */
   for (i = 0; i < imax; i++) {
      for (j = 0; j < jmax; j++)
         printf("%f ",matrix[i][j]);
      printf("\n");
   }

    for (i = 0; i < 2; i++){
        for(j = 0; j < 6; j++){
        fscanf(myFile, "%f", &matrix[i][j] );}
    }

    for (i = 0; i < 2; i++)
    {
        for(j = 0; j < 6; j++){
        printf("Number is: %f\n\n", matrix[i][j]);}
    }

    /* Speicherplatz wieder freigeben.
    * Wichtig! In umgekehrter Reihenfolge. */

   /* Spalten der i-ten Zeile freigeben */
   for(i = 0; i < imax; i++)
      free(matrix[i]);
   /* Jetzt können die leeren Zeilen freigegeben werden. */
   free(matrix);