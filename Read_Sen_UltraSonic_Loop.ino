//---Read the distance at tank------------------------------------
void Read_Sen_UltraSonic_Loop(){
    Val_distance = hc.dist(); // Read Sensor ultrasonic data  
    //Κάνουμε αντιστοίχιση των τιμών του αισθητήρα UltraSonic σε 
    //εκατοστά σε εκατό τις εκατό για την καλύτεροί απεικόνιση της 
    //στάθμης νερού στο δοχείο. Το δοχείο είναι 17 εκατοστά αρά 
    //τότε θα έχει 0% νερό ενώ εάν είναι 0 εκ. τότε έχουμε 100% 
    //νερό μέσα στο δοχείο.
     Val_distancePerCent =   map(Val_distance, 17, 1, 0, 100); 
}
