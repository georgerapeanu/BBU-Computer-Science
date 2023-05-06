import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { HttpClientModule } from '@angular/common/http';

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { LogsOverviewComponent } from './assets/logs-overview/logs-overview.component';
import { ReactiveFormsModule } from '@angular/forms';
import { FormsModule } from '@angular/forms';
import { LogDetailsComponent } from './assets/log-details/log-details.component';
import { LogCreateComponent } from './assets/log-create/log-create.component';
import { LogEditComponent } from './assets/log-edit/log-edit.component';
import { LogDeleteComponent } from './assets/log-delete/log-delete.component';

@NgModule({
  declarations: [
    AppComponent,
    LogsOverviewComponent,
    LogDetailsComponent,
    LogCreateComponent,
    LogEditComponent,
    LogDeleteComponent
  ],
  imports: [
    BrowserModule,
    HttpClientModule,
    ReactiveFormsModule,
    FormsModule,
    AppRoutingModule
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
