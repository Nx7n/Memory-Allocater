#include "allocater.h"

extern heap *memspace;

public void zero(int8 *str, int16 size){
	int8 *p;
	int16 n;
	
	for(n=0, p = str; n<size; n++, p++)
		*p =0;
	
	return; 
}

public bool destroy(void *addr){
	header *p;
	int16 n; 
	void *mem;
	word w;
	
	mem = addr - 8;
	p = $h mem;
	w =  (p->w == ZERO_WORDS) ? 0 : p->w;
	
	((!w) ||(!(p->alloced))) ? ({
		reterr(ErrFree);
	})
	: (void)0;
	
	n = ((p->w-1) *8);
	zero($1 addr, n);
	p->alloced = false;
	
	return true;
}


private header *findBlock_(header *hdr, word allocation, word n){
	bool ok;
	void * mem;
	header  *hdr_;
	word n_, w;
	
	if((n+allocation) > (Maxwords-2))
		reterr(ErrNoMem);
	
	w = (hdr->w == ZERO_WORDS) ? 0  : hdr->w;
	
	ok = (!hdr->w) ? true : ((!(hdr->alloced)) && (hdr->w >= allocation)) ? true : false;
	
	if(ok)
		return hdr;
	else {
		mem = $v (($1 hdr) + (w *8) + 8) ;
		hdr_ = $h mem;
		n_ = n + w;
		
		return findBlock_(hdr_, allocation, n_);
	}
	
	reterr(ErrUnknown);
}

private void *mkalloc(word words, header *hdr) {
	void *ret, *bytesIn, *mem;
	word wordsIn, diff;
	header *hdr_;
	
	bytesIn = $v(($v hdr) - memspace);
	wordsIn = (((word)bytesIn)/8)+1;
	if(words > (Maxwords - wordsIn))
		reterr(ErrNoMem);
	
	if(hdr->w > words){
		diff = hdr->w - words;
		mem = $v (($1 hdr) + (words * 8) + 8);
		hdr_ = $h mem;
		diff--;
		hdr_->w = (!diff) ?  ZERO_WORDS : diff;
		hdr_->alloced = false;
	}
	
	hdr->w = words;
	hdr->alloced = true;
	ret = ($v hdr)+8;
	
	return ret;
}

public void *alloc(int64 bytes) {
	word words;
	header *hdr;
	void *mem;
	
	words = (!(bytes % 8)) ?
				bytes/8: (bytes/8)+1;

	hdr = findBlock(words);
	if(!hdr)
		return $v 0;
	
	
	if (words > Maxwords)
		reterr(ErrNoMem);		

	mem = mkalloc(words, hdr);
	if(!mem)
		return $v 0;
		
		
	return mem;
}

private void show_(header *hdr){
	header *p;
	void *mem;
	int32 n;
	word w; 
	
	for(n= 1, p= hdr, w = (p->w == ZERO_WORDS) ? 0  : p->w; p->w; mem= $v p + ((w+1)*8), p=mem, 
	w = (p->w == ZERO_WORDS) ? 0  : p->w, n++){
		uint64_t size = (uint64_t)w;
		printf("Alloc %d = %"PRIu64 " %s words \n", n, size, (p->alloced)? "alloced" : "free");
		
	}
	return;

}

int main(int argc, char *argv[]){
	int8 *p[MAX];
	int64 size;

	int8 i =0; 
	
	printf("Memspace: %p\n", $v memspace);
	printf("Choose the operation: \n \
		[1] Allocate\n \
		[2] Destroy \n \
		[3] Exit \n "
	  );
	
	while(1){
		int choice;
		printf("\nEnter the choice: ");  
  	   	if (scanf("%d", &choice) != 1) {
		    printf("Invalid input! Please enter a valid number.\n");
		    int c;
		    while ((c = getchar()) != '\n' && c != EOF);  // Clear buffer
		    continue;
    	}
	  	
		if(choice == 1){
			printf("\nEnter the size to be allocated in bytes: ");
			scanf("%llu", &size);
			p[i] = alloc(size);
			i++;
		}
		else if(choice == 2){
			int ind;
			printf("\nEnter the alloc to be destroyed: ");
			scanf("%d", &ind);
			if(ind > 0 && ind <= i)
				destroy(p[ind - 1]);
		}
		
		else if(choice == 3){
			printf("\nQuitting...\n");
			break;
		}
		
		else{ 
			printf("\nInvalid choice!!\n");
			continue;	
		}
		show();
	  	
	}
	
	destroy(p);

	return 0;
}
