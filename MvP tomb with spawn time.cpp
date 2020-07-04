// change it in npc.cpp
// MvP tomb [GreenBox]
void run_tomb(struct map_session_data* sd, struct npc_data* nd)
{
    char buffer[200];
    char time[10];

    strftime(time, sizeof(time), "%H:%M", localtime(&nd->u.tomb.kill_time));

    // TODO: Find exact color?
    snprintf(buffer, sizeof(buffer), msg_txt(sd,657), nd->u.tomb.md->db->name);
    clif_scriptmes(sd, nd->bl.id, buffer);

    clif_scriptmes(sd, nd->bl.id, msg_txt(sd,658));

    snprintf(buffer, sizeof(buffer), "Killer name: ^0000FF%s^000000", nd->u.tomb.killer_name[0] ? nd->u.tomb.killer_name : "Unknown");
    clif_scriptmes(sd, nd->bl.id, buffer);

    snprintf(buffer, sizeof(buffer), msg_txt(sd, 659), time);
    clif_scriptmes(sd, nd->bl.id, buffer);

    const struct TimerData* timer_data = get_timer(nd->u.tomb.md->spawn_timer);
    unsigned int seconds;
    int hours, minutes;

    seconds = (unsigned int)(DIFF_TICK(timer_data->tick, gettick()) / 1000 + 60);
    hours = seconds / (60 * 60);
    seconds = seconds - (60 * 60 * hours);
    minutes = seconds / 60;

    //snprintf(buffer, sizeof(buffer), "Spawn in ^EE0000%d hours %d minutes %d seconds^000000", hours, minutes, seconds);
    snprintf(buffer, sizeof(buffer), "Spawn in ^EE0000%d hours %d minutes^000000", hours, minutes);
    clif_scriptmes(sd, nd->bl.id, buffer);

    clif_scriptclose(sd, nd->bl.id);
}
