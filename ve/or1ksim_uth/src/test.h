#ifndef INCLUDED_TEST_H
#define INCLUDED_TEST_H

typedef void (*uth_busywait_f)(void);

void set_busywait(uth_busywait_f f);

#endif /* INCLUDED_TEST_H */

