#ifndef UTILS_H_
#define UTILS_H_

#include "common/lamp_config.h"


static Notification* SelectNotification(lamp_config_t* config, jenkins_status_t status) {
    Notification* n = NULL;
    for (int i = 0; i < JENKINS_STATUS_NR_ITEMS; i++){
        if (config->notification_list[i].jenkins_status == status) {
            n = &config->notification_list[i];
            break;
        }
    }
    return n;
}

static Color HTMLToColor(String html) {
    Color output;
    sscanf(html.substring(1,3).c_str(), "%2x", &output.red);
    sscanf(html.substring(3,5).c_str(), "%2x", &output.green);
    sscanf(html.substring(5,7).c_str(), "%2x", &output.blue);

    return output;
}

static String ColorToHTML(Color c) {    //TODO(Ortinson): Improve
    String r = String(c.red, HEX);
    if (c.red <= 15)
        r = String("0" + r);

    String g = String(c.green, HEX);
    if (c.green <= 15)
        g = String("0" + g);
        
    String b = String(c.blue, HEX);
    if (c.blue <= 15)
        b = String("0" + b);

    return String("#" + r + g + b);
}

#endif
