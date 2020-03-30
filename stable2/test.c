


int main(int argc, char** argv)
{
	long *i;
	printf("size(i) = %lu %lu %lu\n",sizeof(long),sizeof(i), sizeof(void*));
	i = malloc(10* sizeof(i));
	
	long j = ((long)i << 2);
	printf("%lx %lx %lx %lx %lx \n",i, &i[1] , i + 1, (long*)(j >> 2) + 3, &((long*)(j >> 2))[3]);
	
	return 0;
}