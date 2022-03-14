#ifndef __TOOLS_H__
#define __TOOLS_H__

#define print_stack(start,end,stack)                \
    printf("stack:\n");                             \
    for(int i = start;i <= end;i++)                 \
        fprintf(stderr,"\t%d\n",stack[i]);          \
    printf("\n");

#endif