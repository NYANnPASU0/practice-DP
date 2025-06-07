"""
The task about barbershop, using threading and semaphores.
- Barber sleeps when no customers
- Customers wait in limited chairs or leave if full
- Semaphores synchronize barber/customer threads
"""

import threading
import time
import random
from typing import List, Optional

MAX_CUSTOMERS: int = 5
NUM_CHAIRS: int = 3

barber_semaphore: threading.Semaphore = threading.Semaphore(0)
customer_semaphore: threading.Semaphore = threading.Semaphore(0)
mutex: threading.Semaphore = threading.Semaphore(1)

waiting_customers: List[int] = []
CURRENT_CUSTOMER: Optional[int] = None
IS_BARBER_SLEEPING: bool = True


def barber() -> None:
    """Barber's function, which waits for customers and serves them."""
    global IS_BARBER_SLEEPING, CURRENT_CUSTOMER
    while True:
        mutex.acquire()
        if not waiting_customers:
            if not IS_BARBER_SLEEPING:
                print("The barber is sleeping...")
                IS_BARBER_SLEEPING = True
            mutex.release()
            barber_semaphore.acquire()
            mutex.acquire()
            IS_BARBER_SLEEPING = False

        if waiting_customers:
            CURRENT_CUSTOMER = waiting_customers.pop(0)
            print()
            print(f"The barber is cutting hair for customer {CURRENT_CUSTOMER}")
            mutex.release()
            time.sleep(random.randint(1, 5))
            print(f"The barber has finished cutting hair for customer {CURRENT_CUSTOMER}")
            CURRENT_CUSTOMER = None
            customer_semaphore.release()
        else:
            mutex.release()


def customer(index: int) -> None:
    """Customer function that waits for the barber to cut their hair."""
    global waiting_customers, IS_BARBER_SLEEPING
    time.sleep(random.randint(1, 5))
    mutex.acquire()
    if len(waiting_customers) < NUM_CHAIRS:
        waiting_customers.append(index)
        print(f"Customer {index} is waiting in the waiting room")
        if IS_BARBER_SLEEPING:
            barber_semaphore.release()
            IS_BARBER_SLEEPING = False
        mutex.release()
        customer_semaphore.acquire()
    else:
        print()
        print(f"Customer {index} is leaving because the waiting room is full")
        mutex.release()


def main() -> None:
    """Function to start the barbershop simulation."""
    barber_thread: threading.Thread = threading.Thread(target=barber)
    barber_thread.daemon = True

    customer_threads: List[threading.Thread] = []
    for i in range(MAX_CUSTOMERS):
        customer_threads.append(threading.Thread(target=customer, args=(i,)))

    barber_thread.start()
    for thread in customer_threads:
        thread.start()

    for thread in customer_threads:
        thread.join()
    print()
    print("All customers have been served or left")


if __name__ == "__main__":
    main()
    