struct Clock { 
    int id; 
    int simulating_hz;
};


/**
 * @brief Based on the defined clock configuration it creates a clock that runs at an specified Hz rate
 * 
 * @param defined_clock The clock that is going to be generated
 * @return void
 * 
 */
void *create_clock( void *args );

