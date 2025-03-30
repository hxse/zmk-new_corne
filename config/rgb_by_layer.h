#include <zmk/rgb_underglow.h>
#include <zmk/behavior.h>
#include <zmk/keymap.h>
#include <zmk/event_manager.h>
#include <zmk/events/layer_state_changed.h>

static void update_rgb_color(uint16_t hue, uint8_t saturation, uint8_t brightness) {
    struct zmk_rgb_underglow_config config;
    zmk_rgb_ug_get_config(&config);

    if (config.on) {
        config.hue = hue;
        config.saturation = saturation;
        config.brightness = brightness;

        zmk_rgb_ug_set_config(&config);
        zmk_rgb_ug_apply();
    }
}

ZMK_LISTENER(rgb_layer_listener, layer_state_changed);
ZMK_SUBSCRIPTION(rgb_layer_listener, zmk_layer_state_changed);

int layer_state_changed(const zmk_event_t *eh) {
    uint8_t layer = zmk_keymap_highest_layer_active();
    switch (layer) {
        case 0:
            update_rgb_color(0, 255, 255);    // 红色
            break;
        case 1:
            update_rgb_color(240, 255, 255);  // 蓝色
            break;
        case 2:
            update_rgb_color(120, 255, 255);  // 绿色
            break;
        case 3:
            update_rgb_color(280, 255, 255);  // 紫色
            break;
        default:
            update_rgb_color(30, 255, 255);   // 橙色
            break;
    }
    return 0;
}
