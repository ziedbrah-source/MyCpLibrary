# A and B are executables you want to compare, gen takes int
# as command line arg. Usage: 'sh stress.sh'

    #./bruteforce < int > out2
    #diff -w out1 out2 || break
    # diff -w <(./A < int) <(./B < int) || break
for ((i = 1; ; ++i)); do  # if they are same then will loop forever

    echo $i
    ./gen $i > int
    #./bruteforce < int > out2
    #diff -w out1 out2 || break
     diff -w <(./mtaylor < int) <(./a < int) || break
 
done