void clif_parse_cashshop_open_request( int fd, struct map_session_data* sd ){
	/* Balfear pay2cash system */
	/* Start */
	// Update cashpoints balance from payments order.
	if (Sql_Query(mmysql_handle, "SELECT id, donate FROM `pay2cash` WHERE `account_id` = %d and `status` = 'pending';", sd->status.account_id) != SQL_SUCCESS ) { Sql_ShowDebug(mmysql_handle); }
	if( Sql_NumRows(mmysql_handle) > 0 ) {
		while (SQL_SUCCESS == Sql_NextRow(mmysql_handle)) {
			char* data;
			int id, value;
			char output[128];

			Sql_GetData(mmysql_handle, 0, &data, NULL); id = atoi(data);
			Sql_GetData(mmysql_handle, 1, &data, NULL); value = atoi(data);
			pc_getcash(sd, value, 0, LOG_TYPE_COMMAND);
			sprintf(output, "Order #%d: gained %d cash points.", id, value);
			clif_messagecolor(&sd->bl, color_table[COLOR_LIGHT_GREEN], output, false, SELF);
		}
		Sql_FreeResult(mmysql_handle);
		char output[128];
		sprintf(output, "Total %d cash points.", sd->cashPoints);
		clif_messagecolor(&sd->bl, color_table[COLOR_LIGHT_GREEN], output, false, SELF);
	}
	if( SQL_ERROR == Sql_Query(mmysql_handle, "UPDATE `pay2cash` SET `status` = 'complete' WHERE `account_id` = %d AND `status` = 'pending'", sd->status.account_id) ){ Sql_ShowDebug(mmysql_handle); }
	/* End */

	sd->state.cashshop_open = true;
	sd->npc_shopid = -1; // Set npc_shopid when using cash shop from "cash shop" button [Aelys|Susu] bugreport:96
	clif_cashshop_open( sd );
}