maxNr=0
minNr=10000000
minDist=10000000

read N
P=()
for (( i=0; i<N; i++ )); do
    read Pi

    if (( i > 0 )); then
        if (( $Pi > $maxNr )); then
            dist=$((Pi-maxNr))
            if (( $dist < $minDist )); then
                minDist=$dist
            fi
            maxNr=$Pi
    
        elif (( $Pi < $minNr )); then
            dist=$((minNr-Pi))
            if (( $dist < $minDist )); then
                minDist=$dist
            fi
            minNr=$Pi
    
        else
            for (( j=0; j<i; j++ )); do
                if (( ${P[$j]} < $Pi )); then
                    dist=$((Pi-P[$j]))
                else
                    dist=$((P[$j]-Pi))
                fi 
    
                if (( $dist < $minDist )); then
                    minDist=$dist
                fi
            done
        fi
    else
        maxNr=$Pi
        minNr=$Pi
    fi

    P+=($Pi)
done

echo $minDist
