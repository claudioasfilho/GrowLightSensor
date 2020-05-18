/***************************************************************************//**
 * @file app.c
 * @brief Silicon Labs Empty Example Project
 *
 * This example demonstrates the bare minimum needed for a Blue Gecko C application
 * that allows Over-the-Air Device Firmware Upgrading (OTA DFU). The application
 * starts advertising after boot and restarts advertising after a connection is closed.
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

/* Bluetooth stack headers */
#include "bg_types.h"
#include "native_gecko.h"
#include "gatt_db.h"
#include "thunderboard/si1133.h"
#include "app.h"
#include "calendar.h"

/* Print boot message */
static void bootMessage(struct gecko_msg_system_boot_evt_t *bootevt);

/* Flag for indicating DFU Reset must be performed */
static uint8_t boot_to_dfu = 0;

#define ALS_TIMER_HANDLE (252)

int32_t  RADIO_tempData = 25000;
uint8_t  RADIO_uvIndex = 0;
uint32_t RADIO_ambLight = 0;


void alsMeasurement(){

	uint8_t irqStatus = 0;
	float   lux = 0;
	float   uv = 0;

/* Start an ALS measurement */
  SI1133_measurementForce();

  /* Check if the conversion finished on all channels */
  SI1133_getIrqStatus(&irqStatus);
  if (irqStatus == 0x0F) {

    SI1133_getMeasurement(&lux, &uv);
    RADIO_ambLight = (uint32_t)(lux * 100);
    RADIO_uvIndex = (uint8_t)uv;
    //printf("ES: Amb light = %3.2f Lux\r\n", (float)RADIO_ambLight / 100.0f);
    printf("ES: Amb light = %d Lux\r\n", RADIO_ambLight);
    printf("ES: UV = %d \r\n", (uint8_t)RADIO_uvIndex );
  }

}



/* Main application */
void appMain(gecko_configuration_t *pconfig)
{
#if DISABLE_SLEEP > 0
  pconfig->sleep.flags = 0;
#endif

  /* Initialize debug prints. Note: debug prints are off by default. See DEBUG_LEVEL in app.h */
  initLog();

  set_date_and_time(2020, MAY, 18, MONDAY, 9, 56, 00, 000);
  set_time_zone(8);
  set_dst(0);

  /* Initialize stack */
  gecko_init(pconfig);

  while (1) {
    /* Event pointer for handling events */
    struct gecko_cmd_packet* evt;

    /* if there are no events pending then the next call to gecko_wait_event() may cause
     * device go to deep sleep. Make sure that debug prints are flushed before going to sleep */
    if (!gecko_event_pending()) {
      flushLog();
    }

    /* Check for stack event. This is a blocking event listener. If you want non-blocking please see UG136. */
    evt = gecko_wait_event();

    /* Handle events */
    switch (BGLIB_MSG_ID(evt->header)) {
      /* This boot event is generated when the system boots up after reset.
       * Do not call any stack commands before receiving the boot event.
       * Here the system is set to start advertising immediately after boot procedure. */
      case gecko_evt_system_boot_id:

        bootMessage(&(evt->data.evt_system_boot));
        printLog("boot event - starting advertising\r\n");


        // Setup soft timers
        gecko_cmd_hardware_set_soft_timer(TICKS_PER_SECOND, SEC_TIMER_HANDLE, 0); // 1 sec continuous running
        gecko_cmd_hardware_set_soft_timer(TICKS_PER_SECOND * 60, MINUTE_TIMER_HANDLE, 0); // 1 min continuous running

        gecko_cmd_hardware_set_soft_timer(TICKS_PER_SECOND,ALS_TIMER_HANDLE,0);

        /* Set advertising parameters. 100ms advertisement interval.
         * The first parameter is advertising set handle
         * The next two parameters are minimum and maximum advertising interval, both in
         * units of (milliseconds * 1.6).
         * The last two parameters are duration and maxevents left as default. */
        gecko_cmd_le_gap_set_advertise_timing(0, 160, 160, 0, 0);

        /* Start general advertising and enable connections. */
        gecko_cmd_le_gap_start_advertising(0, le_gap_general_discoverable, le_gap_connectable_scannable);
        break;

      case gecko_evt_le_connection_opened_id:

        printLog("connection opened\r\n");

        break;

      case gecko_evt_gatt_server_user_read_request_id:

        	  switch (evt->data.evt_gatt_server_user_read_request.characteristic)
    		  {
				  case gattdb_AmbientLight:
					  {
						/* Send response to read request */
						gecko_cmd_gatt_server_send_user_read_response(evt->data.evt_gatt_server_user_read_request.connection,gattdb_AmbientLight,0,sizeof(RADIO_ambLight),(uint8_t *)&RADIO_ambLight);
						}
					break;

							//gattdb_UVIndex
				  case gattdb_UVIndex:
					  {
						/* Send response to read request */
						gecko_cmd_gatt_server_send_user_read_response(evt->data.evt_gatt_server_user_read_request.connection,gattdb_UVIndex,0,sizeof(RADIO_uvIndex),(uint8_t *)&RADIO_uvIndex);
						}
					break;

				  case gattdb_current_time_2:
					  {
						struct current_time_characteristic current_time;
						uint16_t ms;
						current_time.adjust_reason = 0x1;
						get_date_and_time((uint16_t *) &(current_time.exact_time.day_date_time.date_time.year), (uint8_t *) &(current_time.exact_time.day_date_time.date_time.month), (uint8_t *) &(current_time.exact_time.day_date_time.date_time.day), (uint8_t *) &(current_time.exact_time.day_date_time.day_of_week), (uint8_t *) &(current_time.exact_time.day_date_time.date_time.hour), (uint8_t *) &(current_time.exact_time.day_date_time.date_time.minute), (uint8_t *) &(current_time.exact_time.day_date_time.date_time.second), &ms);
						current_time.exact_time.frac_256 = ms * 256 / 1000;
						gecko_cmd_gatt_server_send_user_read_response(evt->data.evt_gatt_server_user_read_request.connection, evt->data.evt_gatt_server_user_read_request.characteristic, 0, sizeof(struct current_time_characteristic), (uint8_t const*) &current_time);
					  }
					break;


				  case gattdb_local_time_information:{
			          struct local_time_information_characteristic local_time_info;
			          local_time_info.time_zone = get_time_zone();
			          local_time_info.dst_offset = get_dst();
			          gecko_cmd_gatt_server_send_user_read_response(evt->data.evt_gatt_server_user_read_request.connection, evt->data.evt_gatt_server_user_read_request.characteristic, 0, sizeof(struct local_time_information_characteristic), (uint8_t const*) &local_time_info);
			        }
					break;

			/*
				  case :
					  {

					  }
					break;
					*/
    		  }
       break;
      case gecko_evt_hardware_soft_timer_id:

    	  switch(evt->data.evt_hardware_soft_timer.handle)
    	  {
			  case SEC_TIMER_HANDLE:
					  application_task();
					  GPIO_PinOutToggle(BSP_LED0_PORT, BSP_LED0_PIN);
				  break;
			  case MINUTE_TIMER_HANDLE:
					  update_calendar();

				  break;

			  case ALS_TIMER_HANDLE:
					  alsMeasurement();
				   break;
    	  }

      break;

      case gecko_evt_le_connection_closed_id:

        printLog("connection closed, reason: 0x%2.2x\r\n", evt->data.evt_le_connection_closed.reason);

        /* Check if need to boot to OTA DFU mode */
        if (boot_to_dfu) {
          /* Enter to OTA DFU mode */
          gecko_cmd_system_reset(2);
        } else {
          /* Restart advertising after client has disconnected */
          gecko_cmd_le_gap_start_advertising(0, le_gap_general_discoverable, le_gap_connectable_scannable);
        }
        break;

      /* Events related to OTA upgrading
         ----------------------------------------------------------------------------- */

      /* Check if the user-type OTA Control Characteristic was written.
       * If ota_control was written, boot the device into Device Firmware Upgrade (DFU) mode. */
      case gecko_evt_gatt_server_user_write_request_id:

        if (evt->data.evt_gatt_server_user_write_request.characteristic == gattdb_ota_control) {
          /* Set flag to enter to OTA mode */
          boot_to_dfu = 1;
          /* Send response to Write Request */
          gecko_cmd_gatt_server_send_user_write_response(
            evt->data.evt_gatt_server_user_write_request.connection,
            gattdb_ota_control,
            bg_err_success);

          /* Close connection to enter to DFU OTA mode */
          gecko_cmd_le_connection_close(evt->data.evt_gatt_server_user_write_request.connection);
        }
        break;

      /* Add additional event handlers as your application requires */

      default:
        break;
    }
  }
}

/* Print stack version and local Bluetooth address as boot message */
static void bootMessage(struct gecko_msg_system_boot_evt_t *bootevt)
{
#if DEBUG_LEVEL
  bd_addr local_addr;
  int i;

  printLog("stack version: %u.%u.%u\r\n", bootevt->major, bootevt->minor, bootevt->patch);
  local_addr = gecko_cmd_system_get_bt_address()->address;

  printLog("local BT device address: ");
  for (i = 0; i < 5; i++) {
    printLog("%2.2x:", local_addr.addr[5 - i]);
  }
  printLog("%2.2x\r\n", local_addr.addr[0]);
#endif
}
