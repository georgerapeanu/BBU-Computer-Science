import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { HomeComponent } from './components/home/home.component';
import { UsersOverviewComponent } from './components/users/users-overview/users-overview.component';
import {HttpClientModule, HTTP_INTERCEPTORS} from '@angular/common/http';
import { UserDetailsComponent } from './components/users/user-details/user-details.component';
import { UserEditComponent } from './components/users/user-edit/user-edit.component';
import { FormsModule, ReactiveFormsModule } from '@angular/forms';
import { ProductsScoreStatisticComponent } from './components/products/products-score-statistic/products-score-statistic.component';
import { UserDeleteComponent } from './components/users/user-delete/user-delete.component';
import { PaginationComponent } from './components/reusable/pagination/pagination.component';
import { ManufacturersOverviewComponent } from './components/manufacturers/manufacturers-overview/manufacturers-overview.component';
import { ManufacturerCreateComponent } from './components/manufacturers/manufacturer-create/manufacturer-create.component';
import { ManufacturerDetailsComponent } from './components/manufacturers/manufacturer-details/manufacturer-details.component';
import { ManufacturerEditComponent } from './components/manufacturers/manufacturer-edit/manufacturer-edit.component';
import { ManufacturerDeleteComponent } from './components/manufacturers/manufacturer-delete/manufacturer-delete.component';
import { ProductsOverviewComponent } from './components/products/products-overview/products-overview.component';
import { ProductDetailsComponent } from './components/products/product-details/product-details.component';
import { ProductCreateComponent } from './components/products/product-create/product-create.component';
import { ProductEditComponent } from './components/products/product-edit/product-edit.component';
import { ProductDeleteComponent } from './components/products/product-delete/product-delete.component';
import { UsersOverviewPageComponent } from './components/users/users-overview-page/users-overview-page.component';
import { ManufacturersOverviewPageComponent } from './components/manufacturers/manufacturers-overview-page/manufacturers-overview-page.component';
import { ProductsOverviewPageComponent } from './components/products/products-overview-page/products-overview-page.component';
import { ReviewsOverviewPageComponent } from './components/reviews/reviews-overview-page/reviews-overview-page.component';
import { AbstractOverviewPageComponent } from './components/abstract/abstract-overview-page/abstract-overview-page.component';
import { ReviewDetailsComponent } from './components/reviews/review-details/review-details.component';
import { ReviewCreateComponent } from './components/reviews/review-create/review-create.component';
import { ReviewEditComponent } from './components/reviews/review-edit/review-edit.component';
import { ReviewDeleteComponent } from './components/reviews/review-delete/review-delete.component';
import { ManufacturersCountStatisticComponent } from './components/manufacturers/manufacturers-count-statistic/manufacturers-count-statistic.component';
import { UserReviewCountPageComponent } from './components/users/user-review-count-page/user-review-count-page.component';
import { ManufacturerProductCountPageComponent } from './components/manufacturers/manufacturer-product-count-page/manufacturer-product-count-page.component';
import { ProductScorePageComponent } from './components/products/product-score-page/product-score-page.component';
import { ProductsScoreWithUsersPageComponent } from './components/products/products-score-with-users-page/products-score-with-users-page.component';
import { LoginStatusComponent } from './components/reusable/login-status/login-status.component';
import { RegisterComponent } from './components/login/register/register.component';
import { RegisterConfirmComponent } from './components/login/register-confirm/register-confirm.component';
import { LoginComponent } from './components/login/login/login.component';
import { LogoutComponent } from './components/login/logout/logout.component';
import { AuthInterceptor } from './interceptors/auth.interceptor';
import { AbstractPageContainerComponent } from './components/abstract/abstract-page-container/abstract-page-container.component';
import { UnauthorizedComponent } from './components/unauthorized/unauthorized.component';
import { UnauthorizedRedirectionInterceptor } from './interceptors/unauthorized-redirection.interceptor';
import { AdminComponent } from './components/admin/admin.component';
import { ChatComponent } from './components/chat/chat.component';

@NgModule({
  declarations: [
    AppComponent,
    HomeComponent,
    UsersOverviewComponent,
    UserDetailsComponent,
    UserEditComponent,
    ProductsScoreStatisticComponent,
    UserDeleteComponent,
    PaginationComponent,
    ManufacturersOverviewComponent,
    ManufacturerCreateComponent,
    ManufacturerDetailsComponent,
    ManufacturerEditComponent,
    ManufacturerDeleteComponent,
    ProductsOverviewComponent,
    ProductDetailsComponent,
    ProductCreateComponent,
    ProductEditComponent,
    ProductDeleteComponent,
    UsersOverviewPageComponent,
    ManufacturersOverviewPageComponent,
    ProductsOverviewPageComponent,
    ReviewsOverviewPageComponent,
    AbstractOverviewPageComponent,
    ReviewDetailsComponent,
    ReviewCreateComponent,
    ReviewEditComponent,
    ReviewDeleteComponent,
    ManufacturersCountStatisticComponent,
    UserReviewCountPageComponent,
    ManufacturerProductCountPageComponent,
    ProductScorePageComponent,
    ProductsScoreWithUsersPageComponent,
    LoginStatusComponent,
    RegisterComponent,
    RegisterConfirmComponent,
    LoginComponent,
    LogoutComponent,
    UnauthorizedComponent,
    AdminComponent,
    ChatComponent
  ],
  imports: [
    BrowserModule,
    HttpClientModule,
    FormsModule,
    ReactiveFormsModule,
    AppRoutingModule
  ],
  providers: [
    {provide: HTTP_INTERCEPTORS, useClass: AuthInterceptor, multi: true},
    {provide: HTTP_INTERCEPTORS, useClass: UnauthorizedRedirectionInterceptor, multi: true}
  ],
  bootstrap: [AppComponent]
})
export class AppModule { }
