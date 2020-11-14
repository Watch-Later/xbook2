#include <xbook/safety.h>
#include <xbook/kernel.h>
#include <xbook/schedule.h>
#include <arch/page.h>

int safety_check_range(void *src, unsigned long nbytes)
{
    unsigned long addr;
    addr = (unsigned long) src;
    if (task_current->vmm && (addr >= KERN_VADDR) || (addr + nbytes >= KERN_VADDR)) {
        return -1;
    }
    return 0;
}

int mem_copy_from_user(void *dest, void *src, unsigned long nbytes)
{
    if (safety_check_range(src, nbytes) < 0)
        return -1;
    if (!page_readable((unsigned long) src, nbytes))
        return -1;
    if (dest && src)
        memcpy(dest, src, nbytes);
    return 0;
}

int mem_copy_to_user(void *dest, void *src, unsigned long nbytes)
{
    if (safety_check_range(dest, nbytes) < 0)
        return -1;
    if (!page_writable((unsigned long) dest, nbytes))
        return -1;  
    if (dest && src)
        memcpy(dest, src, nbytes);
    return 0;
}
