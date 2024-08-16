#include <windows.h>
#include <stdio.h>
#include <stdbool.h>

// func to be called whenever a keyboard event occurs
LRESULT CALLBACK keyboard_press_callback(int n_code, WPARAM w_param, LPARAM l_param) {
    if (n_code >= 0) { // process event if not a sys message
        KBDLLHOOKSTRUCT *p_keyboard = (KBDLLHOOKSTRUCT *)l_param; // contains the info about the keyboard event
        if (w_param == WM_KEYDOWN || w_param == WM_SYSKEYDOWN) { // check for a keypress
            UINT vk_code = (UINT)p_keyboard->vkCode; // DWORD --> unsigned int (both unsigned 32-bit)
            char keyname_str[255] = {'\0'}; // initialising the keyname_str to all zeros
            GetKeyNameTextA(p_keyboard->scanCode << 16, keyname_str, sizeof(keyname_str)); // getting keyname --> scancode bit-shifted 16-bits as required by this function
            printf("Key VK: %u | Keyname: %s\n", vk_code, keyname_str); // don't need to handle an invalid get keyname keyname_str is initialised to all zeros
            fflush(stdout); // force all stdout to the console
        }
    }
    return CallNextHookEx(NULL, n_code, w_param, l_param); // passes the hook info to the next hook in the chain
}   

// setup hook to process keyboard events (messages)
bool install_keyboard_hook() {
    HHOOK h_hook = SetWindowsHookEx(WH_KEYBOARD_LL, keyboard_press_callback, NULL, 0); // idHook, callback func, currentprocess, hook applies to all threads 
    if (h_hook == NULL) {
        fprintf(stderr, "error: failed to install the keyboard hook!\n");
        return false;
    }

    // Message loop to keep the hook active
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) { // gets keyboard messages when available
        TranslateMessage(&msg); // translate VK messages into char messages
        DispatchMessageW(&msg); // sends the message to the appropriate window procedure
    }
    UnhookWindowsHookEx(h_hook); // cleanup the windows keyboard hook (free memory)
    return true;
}

int main() {
    bool hook_install_result = install_keyboard_hook();
    if (!hook_install_result) {
        return -1;
    }

    return 0;
}