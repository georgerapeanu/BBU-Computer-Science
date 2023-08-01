import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { UserProfile } from '../model/UserProfile';
import { environment } from 'src/environments/environment';
import { Observable } from 'rxjs';
import { GenericPage } from '../model/GenericPage';
import { Review } from '../model/Review';
import UserReviewCountDTO from '../dto/UserReviewCountDTO';
import { UserCreatedCountDTO } from '../dto/UserCreatedCountDTO';
import { Role } from '../model/Role';

@Injectable({
  providedIn: 'root'
})
export class UserService {

  constructor(private http: HttpClient) { }

  getAllUsers(pageNumber: number, pageSize: number): Observable<GenericPage<UserProfile>> {
    return this.http.get<GenericPage<UserProfile>>(environment.apiURL + "/users" + `?pageNumber=${pageNumber}` + `&pageSize=${[pageSize]}`);
  }

  getUserReviewCountsPage(pageNumber: number, pageSize: number): Observable<GenericPage<UserReviewCountDTO>> {
    return this.http.get<GenericPage<UserReviewCountDTO>>(environment.apiURL + "/user-review-counts" + `?pageNumber=${pageNumber}` + `&pageSize=${[pageSize]}`);
  }

  getAllReviewsForUser(userHandle: string, pageNumber: number, pageSize: number): Observable<GenericPage<Review>> {
    return this.http.get<GenericPage<Review>>(environment.apiURL + "/users" + `/${userHandle}` + "/reviews" + `?pageNumber=${pageNumber}` + `&pageSize=${[pageSize]}`);
  }

  getUserById(userHandle: string): Observable<UserProfile> {
    return this.http.get<UserProfile>(environment.apiURL + "/users/" + userHandle);
  }

  editUser(user: UserProfile): Observable<any>{
    return this.http.patch(environment.apiURL + "/users/" + user.handle, user);
  }

  deleteUser(userHandle: string): Observable<any> {
    return this.http.delete(environment.apiURL + "/users/" + userHandle);
  }

  getUserCreatedCount(userHandle: string): Observable<UserCreatedCountDTO> {
    return this.http.get<UserCreatedCountDTO>(environment.apiURL + "/user-created-count" + "/" + userHandle);
  }

  getUserRole(userHandle: string): Observable<Role> {
    return this.http.get<Role>(environment.apiURL + "/users" + "/" + userHandle + "/role");
  }
}
