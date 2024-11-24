#include <bits/stdc++.h>
#include <ctime>
using namespace std;
#define ll long long int
// Function to simulate the transmission of frames
void transmission(ll &i, ll &N, ll &tf, ll &tt) {
    while (i <= tf) {
        int successful_acks = 0;
// Sending frames within the current window
        for (int k = i; k < i + N && k <= tf; k++) {
            cout << "Sending Frame " << k << "..." << endl;
            tt++; // Increment total transmissions
        }
   // Simulating acknowledgment for the frames
        for (int k = i; k < i + N && k <= tf; k++) {
            int ack = rand() % 2; // Random acknowledgment simulation
            if (ack == 1) {
                cout << "Acknowledgment for Frame " << k << " received." << endl;
                successful_acks++;
            } else {
                cout << "Timeout!! Frame Number " << k << " not acknowledged." << endl;
                cout << "Retransmitting the current window...\n" << endl;
                break; // Break the acknowledgment loop and retransmit
            }
        }
// Move the window forward by the number of successful acknowledgments
        i += successful_acks;
        cout << "\n";
    }
}
int main() {
    ll tf, N, tt = 0; // Total frames, window size, total transmissions
    srand(time(NULL)); // Seed for random acknowledgment simulation
  // Input the total number of frames and the window size
    cout << "Enter the total number of frames: ";
    cin >> tf;
    cout << "Enter the window size: ";
    cin >> N;
    ll i = 1; // Starting frame index
 // Call the transmission function to simulate the protocol
    transmission(i, N, tf, tt);
    // Output the total number of transmissions
    cout << "Total number of frames sent (including retransmissions): " << tt << endl;
    return 0;
}
